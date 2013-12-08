using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace ConsoleApplication1
{
    class Program
    {

        static SerialPort sf;
        
        //variables used for reading from serial port.
        const int BUFF_SIZE = 256;
        static char[] buff = new char[256];
        static int bIndx = 0;
        static bool readingPacket;

        //THIS KEEPS TRACK OF ALL CURRENT CHARGE SESSIONS. When a new charge session is created
        //a copy of this struct is used to store the vid and pid for the session in this list
        //then when receiving voltage the list is checked and can be handled differently to update a session in database or just report debug info.
        struct currentChargeSession
        {
            public string padID;
            public string vehicleID;
        };
        static List<currentChargeSession> currentSessions = new List<currentChargeSession>();


        //TEMPORARY HACK: This list should be handled by database/datamanager, this list should be created/populated by the database when we register cars.
        static List<string> authorizedVehicleIDs = new List<string>();

        static void Main(string[] args)
        {
            sf = new SerialPort();
            sf.PortName = "COM6"; //****ALERT***** HACK: set the com port appropriately before running this program...
            sf.BaudRate = 9600;
            sf.DataBits = 8;
            sf.StopBits = System.IO.Ports.StopBits.One;
            sf.Parity = System.IO.Ports.Parity.None;
            sf.Open();
            sf.DataReceived += uart_rx_handler;


            authorizedVehicleIDs.Add("9ABC"); //TEMPORARY HACK: This list should be handled by database/datamanager

            //this is just for testing so you can manually send commands to the arduino.
            int key;
            int i = 0;
            char[] cmdBuffer = new char[256];
            while ((key = Console.Read()) != -1)
            {
                if (key == '\n')
                {
                    cmdBuffer[i] = '\0';
                    sf.Write(new String(cmdBuffer));
                    Console.WriteLine(new String(cmdBuffer));
                    i = 0;
                }
                else if (i < 256)
                {
                    cmdBuffer[i++] = (char)key;
                }
                else
                {
                    i = 0;
                }
            }
        }

        //receives serial data and finds data framed by [] marks.
        static protected void uart_rx_handler(object sender, SerialDataReceivedEventArgs c)
        {
            int readChar;
            while ((readChar = sf.ReadByte()) != -1)
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
                    processPacket(new string(buff,0,bIndx));
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
        static void processPacket(string packet)
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
        static bool processColorInfoPacket(string[] args)
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
        static bool processVoltageInfoPacket(string[] args)
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
            if (isValidVehicleID(ID) && vehicleIsInChargeSession(ID) )
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
        static bool processCurrentInfoPacket(string[] args)
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
            if (isValidVehicleID(ID) && vehicleIsInChargeSession(ID) )
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
        static bool processChargeBeginPacket(string[] args)
        {
            if (args[1].Length != 2 || args[2].Length != 4)
                return false;

            string padID = args[1];
            string vehicleRadioID = args[2];

            if (isValidPadID(padID) && isValidVehicleID(vehicleRadioID))
            {
                //TODO stuff with information that this vehicle will be beginning a charge session.
                Console.WriteLine("CHARGE SESSION: Start for vehicle " + vehicleRadioID + " on pad " + padID + ".");
                
                currentChargeSession newSession;
                newSession.vehicleID = vehicleRadioID;
                newSession.padID = padID;
                currentSessions.Add(newSession);
                
                return true;
            }

            return false;
        }

        //process notification of charge end
        //removes the current charge session from chargeSessions.
        //probably need to do stuff in database too.
        static bool processChargeEndPacket(string[] args)
        {
            if (args[1].Length != 2 || args[2].Length != 4)
                return false;

            string padID = args[1];
            string vehicleRadioID = args[2];

            if (isValidPadID(padID) && isValidVehicleID(vehicleRadioID))
            {
                //TODO do stuff with information that this vehicle ended a charge session.
                

                foreach (currentChargeSession s in currentSessions)
                {
                    if (s.padID == padID && s.vehicleID == vehicleRadioID) //these should both match, doesn't actually matter to check both
                    {
                        Console.WriteLine("CHARGE SESSION: End for vehicle " + vehicleRadioID + " on pad " + padID + ".");
                        currentSessions.Remove(s);
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


        static bool isValidVehicleID(string ID)
        {
            foreach (string s in authorizedVehicleIDs)
                if (s == ID)
                    return true;

            return false;
        }

        static bool vehicleIsInChargeSession(string ID)
        {
            foreach (currentChargeSession session in currentSessions)
                if (session.vehicleID == ID)
                    return true;

            return false;
        }

        static bool padIsInChargeSession(string ID)
        {
            foreach (currentChargeSession session in currentSessions)
                if (session.padID == ID)
                    return true;

            return false;
        }

    }
}
