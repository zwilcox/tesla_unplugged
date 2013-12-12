using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InductiveCharging
{
    public partial class TestForm : Form
    {
        string rxString;
        DataManager dataManager;
        const int BUFF_SIZE = 256;
        static char[] buff = new char[256];
        static int bIndx = 0;
        static bool readingPacket;

        public TestForm(ref DataManager _manager)
        {
            InitializeComponent();
            //serialPort1.PortName = Properties.Settings.Default.selectedPort;
            dataManager = _manager;
        }

        private void displayText(object sender, EventArgs e)
        {
            testSerialTextBox.AppendText(rxString);
        }

        // Send a string as a command to the Arduino Mega via the USB serial port
        private bool sendCommand(string cmd)
        {
            //if (!serialPort1.IsOpen) return false;  // for use without the DataManager
            if (!dataManager.sendCommand(cmd)) return false;
            else
            {
                // serialPort1.Write("[" + cmd + " ]"); // for use without the DataManager
                //testSerialTextBox.AppendText("tx: [" + cmd + " ]\n");
                return true;
            }
        }

        


        private void testFormCloseButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void TestForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //if (serialPort1.IsOpen) serialPort1.Close();
        }

        // Parse through packets and call appropriate methods accordingly
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
            
            this.Invoke(new EventHandler(displayText));
        }


        /*
         * Start tests for Charging Pad 1
         */

        private void testPad1OnButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TP P1 1"))
            {
                testPad1OnButton.Enabled = false;
                testPad1OffButton.Enabled = true;
            }
            else
            {
                string message = "An error occured trying to send the command to turn on Charging Pad 1.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad1OffButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TP P1 0"))
            {
                testPad1OnButton.Enabled = true;
                testPad1OffButton.Enabled = false;
            }
            else 
            {
                string message = "An error occured trying to send the command to turn off Charging Pad 1.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad1VoltageButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("GV P1"))
            {
                // wait for response from Arduino Mega with Charging Pad 1 voltage reading results
            }
            else
            {
                string message = "An error occured trying to send the command to get the voltage from Charging Pad 1.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad1CurrentButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("GA P1"))
            {
                // wait for response from Arduino Mega with Charging Pad 1 current reading results
            }
            else
            {
                string message = "An error occured trying to send the command to get the current from Charging Pad 1.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad1SensorButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("GC P1"))
            {
                // wait for response fronm Arduino Mega with Charging Pad 1 color sensosr reading results
            }
            else
            {
                string message = "An error occured trying to send the command to get the color sensor value from Charging Pad 1.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad1SensorLEDOnButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TC P1 1"))
            {
                testPad1SensorLEDOnButton.Enabled = false;
                testPad1SensorLEDOffButton.Enabled = true;
            }
            else
            {
                string message = "An error occured trying to send the command to turn on the color sensor LED for Charging Pad 1.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad1SensorLEDOffButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TC P1 0"))
            {
                testPad1SensorLEDOnButton.Enabled = true;
                testPad1SensorLEDOffButton.Enabled = false;
            }
            else
            {
                string message = "An error occured trying to send the command to turn off the color sensor LED for Charging Pad 1.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad1SensorCalibrateButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("CC P1"))
            {
                // wait for response
            }
            else
            {
                string message = "An error occured trying to send the command to calibrate the color sensor for Charging Pad 1.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }


        /*
         * Start tests for Charging Pad 2 
         */

        private void testPad2OnButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TP P2 1"))
            {
                testPad2OnButton.Enabled = false;
                testPad2OffButton.Enabled = true;
            }
            else
            {
                string message = "An error occured trying to send the command to turn on Charging Pad 2.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad2OffButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TP P2 0"))
            {
                testPad2OnButton.Enabled = true;
                testPad2OffButton.Enabled = false;
            }
            else
            {
                string message = "An error occured trying to send the command to turn off Charging Pad 2.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad2VoltageButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("GV P2"))
            {
                // wait for response from Arduino Mega with Charging Pad 2 voltage reading results
            }
            else
            {
                string message = "An error occured trying to send the command to get the voltage from Charging Pad 2.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad2CurrentButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("GA P2"))
            {
                // wait for response from Arduino Mega with Charging Pad 2 current reading results
            }
            else
            {
                string message = "An error occured trying to send the command to get the current from Charging Pad 2.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad2SensorButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("GC P2"))
            {
                // wait for response fronm Arduino Mega with Charging Pad 2 color sensosr reading results
            }
            else
            {
                string message = "An error occured trying to send the command to get the color sensor value from Charging Pad 2.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad2SensorLEDOnButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TC P2 1"))
            {
                testPad2SensorLEDOnButton.Enabled = false;
                testPad2SensorLEDOffButton.Enabled = true;
            }
            else
            {
                string message = "An error occured trying to send the command to turn off the color sensor LED for Charging Pad 2.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad2SensorLEDOffButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TC P2 0"))
            {
                testPad2SensorLEDOnButton.Enabled = true;
                testPad2SensorLEDOffButton.Enabled = false;
            }
            else
            {
                string message = "An error occured trying to send the command to turn off the color sensor LED for Charging Pad 2.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad2SensorCalibrateButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("CC P2"))
            {
                // wait for response
            }
            else
            {
                string message = "An error occured trying to send the command to calibrate the color sensor for Charging Pad 2.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        
        /*
         * Start tests for Charging Pad 3 
         */

        private void testPad3OnButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TP P3 1"))
            {
                testPad3OnButton.Enabled = false;
                testPad3OffButton.Enabled = true;
            }
            else
            {
                string message = "An error occured trying to send the command to turn on Charging Pad 3.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad3OffButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TP P3 0"))
            {
                testPad3OnButton.Enabled = true;
                testPad3OffButton.Enabled = false;
            }
            else
            {
                string message = "An error occured trying to send the command to turn off Charging Pad 3.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad3Voltage_Click(object sender, EventArgs e)
        {
            if (sendCommand("GV P3"))
            {
                // wait for response from Arduino Mega with Charging Pad 3 voltage reading results
            }
            else
            {
                string message = "An error occured trying to send the command to get the voltage from Charging Pad 3.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad3CurrentButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("GA P3"))
            {
                // wait for response from Arduino Mega with Charging Pad 3 current reading results
            }
            else
            {
                string message = "An error occured trying to send the command to get the current from Charging Pad 3.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        // Gets the color sensor reading for Charging Pad 3.
        private void testPad3SensorButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("GC P3"))
            {
                // wait for response fronm Arduino Mega with Charging Pad 3 color sensosr reading results
            }
            else
            {
                string message = "An error occured trying to send the command to get the color sensor value from Charging Pad 3.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        // Turns on the color sensor LED for Charging Pad 3.
        private void testPad3SensorLEDOnButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TC P3 1"))
            {
                testPad3SensorLEDOnButton.Enabled = false;
                testPad3SensorLEDOffButton.Enabled = true;
            }
            else
            {
                string message = "An error occured trying to send the command to turn off the color sensor LED for Charging Pad 3.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad3SensorLEDOffButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("TC P3 0"))
            {
                testPad3SensorLEDOnButton.Enabled = true;
                testPad3SensorLEDOffButton.Enabled = false;
            }
            else
            {
                string message = "An error occured trying to send the command to turn off the color sensor LED for Charging Pad 3.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void testPad3SensorCalibrateButton_Click(object sender, EventArgs e)
        {
            if (sendCommand("CC P3"))
            {
                // wait for response
            }
            else
            {
                string message = "An error occured trying to send the command to calibrate the color sensor for Charging Pad 3.";
                string caption = "Error sending command.";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(message, caption, buttons);
            }
        }

        private void TestDBAddCarButton_Click(object sender, EventArgs e)
        {
            RegisterNewCarForm regCarForm = new RegisterNewCarForm(ref dataManager);
            regCarForm.Show();
        }

        private void testDBListCarsButton_Click(object sender, EventArgs e)
        {

        }

        private void authorizeCarButton_Click(object sender, EventArgs e)
        {

        }

        private void deauthorizeCarButton_Click(object sender, EventArgs e)
        {

        }

        private void clearCarListButton_Click(object sender, EventArgs e)
        {

        }


    }
}
