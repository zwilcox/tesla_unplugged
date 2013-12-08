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

        int i;
        static SerialPort sf;


        const int BUFF_SIZE = 256;
        static char[] buff = new char[256];
        static int bIndx = 0;
        static bool readingPacket;

        static void Main(string[] args)
        {
            sf = new SerialPort();
            sf.PortName = "COM4";
            sf.BaudRate = 9600;
            sf.DataBits = 8;
            sf.StopBits = System.IO.Ports.StopBits.One;
            sf.Parity = System.IO.Ports.Parity.None;
            sf.Open();
            sf.DataReceived += uart_rx_handler;

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


        static protected void uart_rx_handler(object sender, SerialDataReceivedEventArgs c)
        {
            int readChar;
            while ((readChar = sf.ReadByte()) != -1)
            {
                Console.WriteLine((char)readChar);

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
        }

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
                    Console.WriteLine("Got command charge end");
                    break;
                case "BT":
                    Console.WriteLine("Got notification of power-on");
                    break;
                default:
                    errorMessage(packet);
                    break;
            }


        }
        
        static bool processColorInfoPacket(string[] args)
        {
            Console.WriteLine("Got command Send Color");
            
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

                    //ACTUALLY DO STUFF WIT PARSED INFO.
                    //processCarColorInformation(pad, red, green, blue);

                    Console.WriteLine("Got color read (" + red + ", " + green + ", " + blue + ") from pad " + pad + ".");

                    return true;
                }
            }

            return false;
        }

        static bool processVoltageInfoPacket(string[] args)
        {
            Console.WriteLine("Got command Send Voltage");

            if (args[1].Length != 2 || args[1].Length != 4 || args[2].Length!= 6)
                return false;
            
            if (args[2].IndexOf("V") != 6)
                return false;

            float voltage;

            try
            {
                voltage = float.Parse(args[2]);
            }
            catch
            {
                return false;
            }

            string ID = args[1];

            if (isValidPadID(ID))
            {
                //actually do stuff with parsed info.
                //got information about pad voltage.
                Console.WriteLine("Got voltage read from pad: " + voltage);
                return true;
            }
            if (isValidVehicleID(ID))
            {
                //actually do stuff with parsed info.
                //got information about car voltage.
                Console.WriteLine("Got voltage read from car: " + voltage);
                return true;
            }
            else
            {
                return false;
            }
        }

        static bool processCurrentInfoPacket(string[] args)
        {
            Console.WriteLine("Got command Send Current");

            if (args[1].Length != 2 || args[1].Length != 4 || args[2].Length != 6)
                return false;

            if (args[2].IndexOf("A") != 6)
                return false;

            float amps;

            try
            {
                amps = float.Parse(args[2]);
            }
            catch
            {
                return false;
            }

            string ID = args[1];

            if (isValidPadID(ID))
            {
                //actually do stuff with parsed info.
                //got information about pad voltage.
                Console.WriteLine("Got current read from pad: " + amps);
                return true;
            }
            if (isValidVehicleID(ID))
            {
                //actually do stuff with parsed info.
                //got information about car voltage.
                Console.WriteLine("Got current read from car: " + amps);
                return true;
            }
            else
            {
                return false;
            }

        }

        static bool processChargeBeginPacket(string[] args)
        {
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
            //if list of cars in charge sessions contains ID, return true.
            return true;
        }
    }
}
