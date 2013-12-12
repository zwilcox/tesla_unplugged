

﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;
using System.Collections;

namespace InductiveCharging
{
    public class DataManager
    {

        public SerialPort baseStationSerialPort;
        string cmdString;
        //string command;
        TestForm testForm;
        public ArrayList currentSessions = new ArrayList();
        public ArrayList authorizedVehicles = new ArrayList();
        Car newCar;
        public bool isRegistering = false;

        int chargeSessionID = 0;

        // These bools are set true if the following request has been made to the base station
        // They are set false once a reply has been seen
        public bool voltReqP1 = false;     // voltage request for pad 1
        public bool ampReqP1 = false;      // current request for pad 1
        public bool colorReqP1 = false;    // color request for pad 1
        public bool colorCalP1 = false;    // color sensor calibrate request for pad 1
        public bool voltReqP2 = false;     // voltage request for pad 2
        public bool ampReqP2 = false;      // current request for pad 2
        public bool colorReqP2 = false;    // color request for pad 2
        public bool colorCalP2 = false;    // color sensor calibrate request for pad 2
        public bool voltReqP3 = false;     // voltage request for pad 3
        public bool ampReqP3 = false;      // current request for pad 3
        public bool colorReqP3 = false;    // color request for pad 3
        public bool colorCalP3 = false;    // color sensor calibrate request for pad 3

        const int BUFF_SIZE = 256;
        static char[] buff = new char[256];
        static int bIndx = 0;
        static bool readingPacket;

        //defines the type of function to call when color is received:
        public delegate void ColorReceivedEventHandler();
        public event ColorReceivedEventHandler colorChangedEvent;

        private INDUCTIVEDataSetTableAdapters.CarsTableAdapter carsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.ChargeSessionsTableAdapter chargeSessionsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad1AmpsTableAdapter pad1AmpsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad1VoltsTableAdapter pad1VoltsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad2AmpsTableAdapter pad2AmpsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad2VoltsTableAdapter pad2VoltsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad3AmpsTableAdapter pad3AmpsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad3VoltsTableAdapter pad3VoltsTableAdapter;
        private INDUCTIVEDataSet dataSet;

        public DataManager(INDUCTIVEDataSet data, INDUCTIVEDataSetTableAdapters.TableAdapterManager tableAdapterManager )
        {
            //TODO: initialize authorizedVehicleIDs list
            baseStationSerialPort = new SerialPort(Properties.Settings.Default.selectedPort);
            if (baseStationSerialPort.PortName != "")
            {
                baseStationSerialPort.Open();
            }
            else MessageBox.Show("Serial Port Error.", "Error", MessageBoxButtons.OK);

            carsTableAdapter = tableAdapterManager.CarsTableAdapter;
            chargeSessionsTableAdapter = tableAdapterManager.ChargeSessionsTableAdapter;

            dataSet = data;
            pad1AmpsTableAdapter = tableAdapterManager.pad1AmpsTableAdapter;
            pad1VoltsTableAdapter = tableAdapterManager.pad1VoltsTableAdapter;
            pad2AmpsTableAdapter = tableAdapterManager.pad2AmpsTableAdapter;
            pad2VoltsTableAdapter = tableAdapterManager.pad2VoltsTableAdapter;
            pad3AmpsTableAdapter = tableAdapterManager.pad3AmpsTableAdapter;
            pad3VoltsTableAdapter = tableAdapterManager.pad3VoltsTableAdapter;

            baseStationSerialPort.DataReceived += baseStationSerialPort_DataReceived;
        }

        public void setTestForm(TestForm _testForm)
        {
            testForm = _testForm;
        }

        public bool openComPort()
        {
            if (!baseStationSerialPort.IsOpen)
            {
                baseStationSerialPort.Open();
                return true;
            }
            else return false;
        }

        public bool sendCommand(string cmd)
        {
            if (!baseStationSerialPort.IsOpen) return false;
            else
            {
                cmdString = "[" + cmd + " ]";
                baseStationSerialPort.Write(cmdString);
                if (testForm != null)
                {
                    testForm.Invoke(new EventHandler(displayText));
                }
                return true;
            }
            
        }

        public void registeringCar(ref Car _newCar)
        {
            newCar = _newCar;
            isRegistering = true;
        }

        public void carRegistrationComplete()
        {
            isRegistering = false;
            
            
            if(addCarToDB(newCar))
                sendAuthorizedCarInfo(newCar);

            populateAuthorizedCarsList();
        }

        private bool addCarToDB(Car newCar)
        {
            carsTableAdapter.Insert(
                newCar.carID,
                DateTime.Now,
                newCar.pad1Color.red,
                newCar.pad1Color.green,
                newCar.pad1Color.blue,
                newCar.pad2Color.red,
                newCar.pad2Color.green,
                newCar.pad2Color.blue,
                newCar.pad3Color.red,
                newCar.pad3Color.green,
                newCar.pad3Color.blue,
                true);

            try
            {
                carsTableAdapter.Update(dataSet);    // send it to the database
                return true;
            }
            catch
            {
                return false;
            }
        }

        private void populateAuthorizedCarsList()
        {
            authorizedVehicles.Clear();

            System.Data.DataTable t = carsTableAdapter.GetCars();
            
            foreach (System.Data.DataRow r in t.Rows)
            {
                Car newCar = new Car(r["carNumber"].ToString(), r["carID"].ToString());

                newCar.pad1Color.red = r["pad1Red"].ToString();
                newCar.pad1Color.green = r["pad1Green"].ToString();
                newCar.pad1Color.blue = r["pad1Blue"].ToString();
                newCar.pad2Color.red = r["pad2Red"].ToString();
                newCar.pad2Color.green = r["pad2Green"].ToString();
                newCar.pad2Color.blue = r["pad2Blue"].ToString();
                newCar.pad3Color.red = r["pad3Red"].ToString();
                newCar.pad3Color.green = r["pad3Green"].ToString();
                newCar.pad3Color.blue = r["pad3Blue"].ToString();

                authorizedVehicles.Add(newCar);
            }
        }

        private void sendAuthorizedCarInfo(Car newCar)
        {
            string P1color = "[IC P1 " + newCar.radioID + " R" + newCar.pad1Color.red + " G" + newCar.pad1Color.green + " B" + newCar.pad1Color.blue + " ]";
            string P2color = "[IC P2 " + newCar.radioID + " R" + newCar.pad2Color.red + " G" + newCar.pad2Color.green + " B" + newCar.pad2Color.blue + " ]";
            string P3color = "[IC P3 " + newCar.radioID + " R" + newCar.pad3Color.red + " G" + newCar.pad3Color.green + " B" + newCar.pad3Color.blue + " ]";
            baseStationSerialPort.Write(P1color);
            baseStationSerialPort.Write(P2color);
            baseStationSerialPort.Write(P3color);
        }

        public void baseStationSerialPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            //rxString = baseStationSerialPort.ReadExisting();
            //if (testForm != null)
            //{
            //    testForm.Invoke(new EventHandler(displayText));
            //}

            // parse the incoming data and do stuff with it
            // TODO: all receive code

            int readChar;
            while ((readChar = baseStationSerialPort.ReadByte()) != -1)
            {
                if (readChar == '[')
                {
                    bIndx = 0;
                    readingPacket = true;
                }

                else if (readingPacket && readChar == ']')
                {
                    readingPacket = false;
                    buff[bIndx] = '\0';
                    cmdString = new string(buff, 0, bIndx) + "\n";
                    if (testForm != null)
                    {
                        testForm.Invoke(new EventHandler(displayText));
                    }
                    processPacket(new string(buff, 0, bIndx));
                    bIndx = 0;
                }

                else if (readingPacket)
                {
                    buff[bIndx++] = (char)readChar;
                }

                if (bIndx >= BUFF_SIZE - 1)
                {
                    readingPacket = false;
                    bIndx = 0;
                }
            }
            
        }

        //this function processes a packet after it has been found by the uart_rx_handler function.
        //this function forwards the arguments to the parsing function, and will return and error message packet fails to parse.
        private void processPacket(string packet)
        {
            string[] args = packet.Split(' ');
            string cmd = args[0];

            if (cmd.Length > 2)
            {
                errorMessage(packet);
                return;
            }

            switch (cmd)
            {
                case "SC":
                    if (!processColorInfoPacket(args))
                        errorMessage(packet);
                    break;
                case "SV":
                    if (!processVoltageInfoPacket(args))
                        errorMessage(packet);
                    break;
                case "SA":
                    if (!processCurrentInfoPacket(args))
                        errorMessage(packet);
                    break;
                case "CB":
                    if (!processChargeBeginPacket(args))
                        errorMessage(packet);
                    break;
                case "CE":
                    if (!processChargeEndPacket(args))
                        errorMessage(packet);
                    break;
                case "BT":
                    Console.WriteLine("Got notification of power-on");
                    //TODO: send list of cars to basestation.
                    break;
                default:
                    errorMessage(packet);
                    break;
            }


        }

        //processes a get-color string.
        //one valid case:
        //  color string parsed successfully.
        //
        //potentially two cases if you handle color receive differently when registering cars.
        private bool processColorInfoPacket(string[] args)
        {
            //check lengths of arguments.
            if (args[1].Length > 2 || args[2].Length > 5 || args[3].Length > 5 || args[4].Length > 5)
            {
                return false;
            }
            
            //check validity of padID.
            else if (isValidPadID(args[1]))
            {
                string pad = args[1];

                //check validity of color 
                if (args[2].IndexOf("R") != 0 || args[3].IndexOf("G") != 0 || args[4].IndexOf("B") != 0)
                {
                    return false;
                }
                else
                {
                    string red = args[2].Substring(1, 4);
                    string green = args[3].Substring(1, 4);
                    string blue = args[4].Substring(1, 4);

                    //TODO DO STUFF WIT PARSED INFO.
                    //processCarColorInformation(pad, red, green, blue);
                    if (isRegistering)
                    {
                        switch (pad)
                        {
                            case "P1":
                                newCar.pad1Color.red = red;
                                newCar.pad1Color.green = green;
                                newCar.pad1Color.blue = blue;
                                break;
                            case "P2":
                                newCar.pad2Color.red = red;
                                newCar.pad2Color.green = green;
                                newCar.pad2Color.blue = blue;
                                break;
                            case "P3":
                                newCar.pad3Color.red = red;
                                newCar.pad3Color.green = green;
                                newCar.pad3Color.blue = blue;
                                break;
                        }
                    }

                    if (colorChangedEvent != null)
                        colorChangedEvent();

                    Console.WriteLine("color read (" + red + ", " + green + ", " + blue + ") from pad " + pad + ".");

                    return true;
                }
            }

            return false;
        }

        //processes voltage information string. 
        //three valid cases: 
        //  voltage from a pad when not in charge session, 
        //  voltage from a pad when in charge session, 
        //  voltage from a car when in charge session.
        private bool processVoltageInfoPacket(string[] args)
        {
            if ((args[1].Length != 2 && args[1].Length != 4) || args[2].Length != 6)
            {
                return false;
            }
            if (args[2].IndexOf("V") != 5) //find 'V' in 6th position (5th index)
            {
                return false;
            }
            float voltage;

            try
            {
                voltage = float.Parse(args[2].Substring(0, 5)); //use substring to parse only '00.00' instead of '00.00V' which would throw exception
            }
            catch
            {
                Console.WriteLine("float parse error");
                return false;
            }

            string ID = args[1];

            if (isValidPadID(ID))
            {
                if(padIsInChargeSession(ID))
                {
                    //TODO do stuff with parsed info.
                    //got information about pad voltage for a CURRENT CHARGE SESSION.
                    Console.WriteLine("CHARGE SESSION: voltage read " + voltage + " from pad: " + ID);
                }
                else
                {
                    //TODO do stuff with parsed info.
                    //got information about pad voltage.
                    Console.WriteLine("voltage read " + voltage + " from pad: " + ID);
                }
                return true;
            }
            if (isValidVehicleRadioID(ID) && vehicleIsInChargeSession(ID))
            {
                //TODO do stuff with parsed info.
                //got information about car voltage for a CURRENT CHARGE SESSION.
                Console.WriteLine("CHARGE SESSION: voltage read " + voltage + " from car: " + ID);
                return true;
            }
            else
            {
                return false;
            }
        }

        //processes current information string. 
        //three valid cases: 
        //  current from a pad when not in charge session, 
        //  current from a pad when in charge session, 
        //  current from a car when in charge session.
        private bool processCurrentInfoPacket(string[] args)
        {
            if ((args[1].Length != 2 && args[1].Length != 4) || args[2].Length != 6) //valid length of 2 or 4 for args1 length (vehicle or pad id)
                return false;

            if (args[2].IndexOf("A") != 5) //find 'V' in 6th position (5th index)
                return false;

            float amps;

            try
            {
                amps = float.Parse(args[2].Substring(0,5)); //use substring to parse only '00.00' instead of '00.00A' which would throw exception
            }
            catch
            {
                Console.WriteLine("float parse error");
                return false;
            }

            string ID = args[1];

            if (isValidPadID(ID))
            {
                if (padIsInChargeSession(ID))
                {
                    //TODO do stuff with parsed info.
                    //got information about pad voltage. FOR A CURRENT CHARGE SESSION
                    Console.WriteLine("CHARGE SESSION: current read " + amps + " from pad: " + ID);
                }
                else
                {
                    //TODO do stuff with parsed info.
                    //got information about pad voltage.
                    Console.WriteLine("current read " + amps + " from pad: " + ID);
                }
                return true;
            }
            if (isValidVehicleRadioID(ID) && vehicleIsInChargeSession(ID))
            {
                //TODO do stuff with parsed info.
                //got information about car voltage for a CURRENT CHARGE SESSION.
                Console.WriteLine("CHARGE SESSION: current read " + amps + " from car: " + ID);
                return true;
            }
            else
            {
                return false;
            }

        }

        //process notification of charge begin
        //creates a currentChargeSession and adds it to chargeSessions
        //probably need to do stuff in database too.
        public bool processChargeBeginPacket(string[] args)
        {
            if (args[1].Length != 2 || args[2].Length != 4)
                return false;

            string padID = args[1];
            string vehicleRadioID = args[2];

            if (isValidPadID(padID) && isValidVehicleRadioID(vehicleRadioID))
            {
                //TODO stuff with information that this vehicle will be beginning a charge session.
                Console.WriteLine("CHARGE SESSION: Start for vehicle " + vehicleRadioID + " on pad " + padID + ".");
                
                // currentChargeSession newSession;
                //newSession.vehicleID = vehicleRadioID;
                //newSession.padID = padID;
                //currentSessions.Add(newSession);

                ChargeSession newSession = new ChargeSession();
                newSession.radioID = vehicleRadioID;
                newSession.padID = padID;
                newSession.chargeBeginTime = DateTime.Now;
                newSession.sessionID = "" + chargeSessionID++;
                currentSessions.Add(newSession);

                chargeSessionsTableAdapter.Insert(newSession.radioID, newSession.padID, newSession.chargeBeginTime, newSession.chargeBeginTime);
                chargeSessionsTableAdapter.Update(dataSet);

                return true;
            }

            return false;
        }

        //process notification of charge end
        //removes the current charge session from chargeSessions.
        //probably need to do stuff in database too.
        private bool processChargeEndPacket(string[] args)
        {
            DateTime endTime = DateTime.Now;
            if (args[1].Length != 2 || args[2].Length != 4)
                return false;

            string padID = args[1];
            string vehicleRadioID = args[2];

            if (isValidPadID(padID) && isValidVehicleRadioID(vehicleRadioID))
            {
                //TODO do stuff with information that this vehicle ended a charge session.
                

                foreach (ChargeSession s in currentSessions)
                {
                    if (s.padID == padID && s.radioID == vehicleRadioID) //these should both match, doesn't actually matter to check both
                    {
                        Console.WriteLine("CHARGE SESSION: End for vehicle " + vehicleRadioID + " on pad " + padID + ".");
                        currentSessions.Remove(s);

                        System.Data.DataRow[] rows = dataSet.Tables["chargeSessionsTable"].Select("carID = '" + vehicleRadioID + "', startTime = " + s.chargeBeginTime.ToString());

                        foreach (System.Data.DataRow r in rows)
                        {
                            if (r["endTime"] == r["startTime"])
                            {
                                r["endTime"] = endTime;
                            }
                        }

                        chargeSessionsTableAdapter.Update(dataSet);

                        return true;
                    }

                }

                Console.WriteLine("Not in charge session " + vehicleRadioID + " on pad " + padID + ".");
                return false; //current charge session was not on list..
                
            }

            return false;
        }

        /*** HELPER FUNCTIONS ***/

        static bool isValidPadID(string ID)
        {
            return (ID == "P1" || ID == "P2" || ID == "P3");
        }

        
        static void errorMessage(string badPkt)
        {
            Console.WriteLine("Invalid Packet: " + badPkt);
        }


        public bool isValidVehicleRadioID(string ID)
        {
            foreach (Car carToCheck in authorizedVehicles)
                if (carToCheck.radioID == ID)
                    return true;

            return false;
        }

        public bool vehicleIsInChargeSession(string ID)
        {
            foreach (ChargeSession session in currentSessions)
                if (session.radioID == ID)
                    return true;

            return false;
        }

        public bool padIsInChargeSession(string ID)
        {
            foreach (ChargeSession session in currentSessions)
                if (session.padID == ID)
                    return true;

            return false;
        }


        // add text to the serial monitor on the test form
        public void displayText(object sender, EventArgs e)
        {
            testForm.testSerialTextBox.AppendText(cmdString);
        }


        /*
         *  Send Commands for Pad 1 
         */
        public bool turnPad1On()
        {
            if (sendCommand("TP P1 1"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool turnPad1Off()
        {
            if (sendCommand("TP P1 0"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool getPad1Voltage()
        {
            if (sendCommand("GV P1"))
            {
                voltReqP1 = true;   // set flag for sent command waiting for reply
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool getPad1Current()
        {
            if (sendCommand("GA P1"))
            {
                ampReqP1 = true;    // set flag for sent command waiting for reply
                return true;
            }
            else
            {
                return false;
            }
        }

        public PadColor getPad1Color()
        {
            if (sendCommand("GC P1"))
            {
                colorReqP1 = true;  // set flag for sent command waiting for reply
                return null;        // TODO: return actual colors
            }
            else
            {
                return null;
            }
        }

        public bool turnPad1SensorLEDOn()
        {
            if (sendCommand("TC P1 1"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool turnPad1SensorLEDOff()
        {
            if (sendCommand("TC P1 0"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool calibratePad1Color()
        {
            if (sendCommand("CC P1"))
            {
                colorCalP1 = true;  // set flag for sent command waiting for reply
                return true;
            }
            else
            {
                return false;
            }
        }


        /*
         *  Send Commands for Pad 2
         */
        public bool turnPad2On()
        {
            if (sendCommand("TP P2 1"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool turnPad2Off()
        {
            if (sendCommand("TP P2 0"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool getPad2Voltage()
        {
            if (sendCommand("GV P2"))
            {
                voltReqP2 = true;   // set flag for sent command waiting for reply
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool getPad2Current()
        {
            if (sendCommand("GA P2"))
            {
                ampReqP2 = true;    // set flag for sent command waiting for reply
                return true;
            }
            else
            {
                return false;
            }
        }

        public PadColor getPad2Color()
        {
            if (sendCommand("GC P2"))
            {
                colorReqP2 = true;  // set flag for sent command waiting for reply
                return null;        // TODO: return actual color
            }
            else
            {
                return null;
            }
        }

        public bool turnPad2SensorLEDOn()
        {
            if (sendCommand("TC P2 1"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool turnPad2SensorLEDOff()
        {
            if (sendCommand("TC P2 0"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool calibratePad2Color()
        {
            if (sendCommand("CC P2"))
            {
                colorCalP2 = true;  // set flag for sent command waiting for reply
                return true;
            }
            else
            {
                return false;
            }
        }


        /*
         *  Send Commands for Pad 3 
         */
        public bool turnPad3On()
        {
            if (sendCommand("TP P3 1"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool turnPad3Off()
        {
            if (sendCommand("TP P3 0"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool getPad3Voltage()
        {
            if (sendCommand("GV P3"))
            {
                voltReqP3 = true;   // set flag for sent command waiting for reply
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool getPad3Current()
        {
            if (sendCommand("GA P3"))
            {
                ampReqP3 = true;    // set flag for sent command waiting for reply
                return true;
            }
            else
            {
                return false;
            }
        }

        public PadColor getPad3Color()
        {
            if (sendCommand("GC P3"))
            {
                colorReqP3 = true;  // set flag for sent command waiting for reply
                return null;        // TODO: return actual colors
            }
            else
            {
                return null;
            }
        }

        public bool turnPad3SensorLEDOn()
        {
            if (sendCommand("TC P3 1"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool turnPad3SensorLEDOff()
        {
            if (sendCommand("TC P3 0"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool calibratePad3Color()
        {
            if (sendCommand("CC P3"))
            {
                colorCalP3 = true;  // set flag for sent command waiting for reply
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
