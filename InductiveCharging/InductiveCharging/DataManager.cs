using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;

namespace InductiveCharging
{
    public class DataManager
    {

        public SerialPort baseStationSerialPort = new SerialPort(Properties.Settings.Default.selectedPort);
        string rxString;
        string command;
        TestForm testForm;

        // These bools are set true if the following request has been made to the base station
        // They are set false once a reply has been seen
        bool voltReqP1 = false;     // voltage request for pad 1
        bool ampReqP1 = false;      // current request for pad 1
        bool colorReqP1 = false;    // color request for pad 1
        bool colorCalP1 = false;    // color sensor calibrate request for pad 1
        bool voltReqP2 = false;     // voltage request for pad 2
        bool ampReqP2 = false;      // current request for pad 2
        bool colorReqP2 = false;    // color request for pad 2
        bool colorCalP2 = false;    // color sensor calibrate request for pad 2
        bool voltReqP3 = false;     // voltage request for pad 3
        bool ampReqP3 = false;      // current request for pad 3
        bool colorReqP3 = false;    // color request for pad 3
        bool colorCalP3 = false;    // color sensor calibrate request for pad 3

        public void setTestForm(TestForm _testForm)
        {
            testForm = _testForm;
        }

        public bool sendCommand(string cmd)
        {
            if (!baseStationSerialPort.IsOpen) return false;
            else
            {
                baseStationSerialPort.Write("[" + cmd + " ]");
                return true;
            }
        }


        const int BUFF_SIZE = 256;
        static char[] buff = new char[256];
        static int bIndx = 0;
        static bool readingPacket;


        public void baseStationSerialPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int readChar = baseStationSerialPort.ReadByte();

            if (readChar == '[')
            {
                bIndx = 0;
                readingPacket = true;
            }

            else if (readingPacket && readChar == ']')
            {
                readingPacket = false;
                buff[bIndx] = '\0';
                processPacket(new string(buff));
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

        private void processPacket(string pkt)
        {
            rxString = pkt;

            string[] args = pkt.Split(' ');
            string cmd = args[0];

            switch (cmd)
            {
                case "SC":
                    //rxString = "Got a color back";
                    break;
                default:

                    break;
            }


            if (testForm != null)
            {
                testForm.Invoke(new EventHandler(displayText));
            }
        }

        // add text to the serial monitor on the test form
        public void displayText(object sender, EventArgs e)
        {
            testForm.testSerialTextBox.AppendText(rxString + "\n");
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
