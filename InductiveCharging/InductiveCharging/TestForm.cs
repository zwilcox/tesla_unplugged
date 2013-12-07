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
        DataManager manager;

        public TestForm(ref DataManager _manager)
        {
            InitializeComponent();
            serialPort1.PortName = Properties.Settings.Default.selectedPort;
            manager = _manager;
        }

        private void displayText(object sender, EventArgs e)
        {
            testSerialTextBox.AppendText(rxString);
        }

        // Send a single char as a command to the Arduino Mega via the USB serial port
        private bool sendCommand(string cmd)
        {
            if (!serialPort1.IsOpen) return false;
            else
            {
                //char[] buff = new char[1];
                //buff[0] = cmd;
                serialPort1.Write("[" + cmd + " ]");
                testSerialTextBox.AppendText("tx: [" + cmd + " ]\n");
                return true;
            }
        }

        
        // Send Command to Arduino Mega on Base Station to send back its ID
        private void testBaseCommButton_Click(object sender, EventArgs e)
        {
            // TODO
            //if (!serialPort1.IsOpen)
            //{
            //    serialPort1.Open();
            //}
            //serialPort1.WriteLine("5");
        }

        private void testSerialMonitorStartButton_Click(object sender, EventArgs e)
        {
//            serialPort1.PortName = "COM6";
//            serialPort1.BaudRate = 9600;

            serialPort1.Open();
            if (serialPort1.IsOpen)
            {
                testSerialMonitorStartButton.Enabled = false;
                testSerialMonitorStopButton.Enabled = true;
                testSerialTextBox.ReadOnly = false;
            }
        }

        private void testSerialMonitorStopButton_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                //serialPort1.Close();
                testSerialMonitorStartButton.Enabled = true;
                testSerialMonitorStopButton.Enabled = false;
                testSerialTextBox.ReadOnly = true;
            }
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            //if (!serialPort1.IsOpen) return;
            //else
            //{
            //    char[] buff = new char[1];
            //    buff[0] = e.KeyChar;
            //    serialPort1.Write(buff, 0, 1);
            //    e.Handled = true;
            //}
            if (sendCommand("" + e.KeyChar))
            {
                e.Handled = true;
            }
            
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            rxString = serialPort1.ReadExisting();
            this.Invoke(new EventHandler(displayText));
        }

        private void testFormCloseButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void TestForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //if (serialPort1.IsOpen) serialPort1.Close();
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
                testPad1SensorLEDOnButton.Enabled = false;
                testPad1SensorLEDOffButton.Enabled = true;
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
                testPad1SensorLEDOnButton.Enabled = true;
                testPad1SensorLEDOffButton.Enabled = false;
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
                testPad1SensorLEDOnButton.Enabled = false;
                testPad1SensorLEDOffButton.Enabled = true;
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
                testPad1SensorLEDOnButton.Enabled = true;
                testPad1SensorLEDOffButton.Enabled = false;
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
            RegisterNewCarForm regCarForm = new RegisterNewCarForm(ref manager);
            regCarForm.Show();
        }

    }
}
