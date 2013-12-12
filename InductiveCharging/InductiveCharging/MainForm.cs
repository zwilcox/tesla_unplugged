using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;

namespace InductiveCharging
{
    public partial class MainForm : Form
    {
        public string megaComPort;
        private string[] portsList;
        private ArrayList chargeSessions;
        ArrayList cars;
        DataManager dataManager;
        

        public MainForm()
        {
            InitializeComponent();
            getComPorts();
            dataManager = new DataManager(inductiveDataSet1, tableAdapterManager1);
        }

        // Exit the system and close the application
        private void exitButton_Click(object sender, EventArgs e)
        {
            // TODO: turn off all charging pads
            this.Close();
        }

        // Start the System in Test Mode
        private void systemTestsButton_Click(object sender, EventArgs e)
        {
            if (tableAdapterManager1.CarsTableAdapter == null)
            {
                if (MessageBox.Show("Could not connect to database. Please check connection and restart program.", "Error", MessageBoxButtons.OK) == System.Windows.Forms.DialogResult.OK)
                {
                    return;
                }
            }

            

            if (Properties.Settings.Default.selectedPort == "")
            {
                MessageBox.Show("Please select a serial port for the Base Station.", "Port Selection Error", MessageBoxButtons.OK);
                return;
            }
            else
            {
                TestForm tests = new TestForm(ref dataManager);
                dataManager.setTestForm(tests);
                tests.Show();
            }
        }

        // Get a list of current serial ports
        private void getComPorts()
        {
            portsList = System.IO.Ports.SerialPort.GetPortNames();
            portsComboBox.Items.AddRange(portsList);

            // Look for the previously selected port and select it by default
            if (Properties.Settings.Default.selectedPort != "")
            {
                if (portsList.Contains(Properties.Settings.Default.selectedPort))
                {
                    for (int i=0; i<portsList.Count(); i++)
                    {
                        if (portsList[i] == Properties.Settings.Default.selectedPort)
                        {
                            portsComboBox.SelectedIndex = i;
                        }
                    }
                }
            }

        }

        // Set serial port based on selection
        private void portsComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            Properties.Settings.Default.selectedPort = portsComboBox.Text;
            serialPort1.PortName = Properties.Settings.Default.selectedPort;
            Properties.Settings.Default.Save();
        }

        // Start the main automated system
        private void startButton_Click(object sender, EventArgs e)
        {
            if (!dataManager.openComPort())
            {
                MessageBox.Show("Could not open communication port to Base Station.", "Error", MessageBoxButtons.OK);
                return;
            }

            if (tableAdapterManager1.CarsTableAdapter == null)
            {
                if (MessageBox.Show("Could not connect to database. Please check connection and restart program.", "Error", MessageBoxButtons.OK) == System.Windows.Forms.DialogResult.OK)
                {
                    return;
                }
            }

            
            if (Properties.Settings.Default.selectedPort == "")
            {
                MessageBox.Show("Please select a serial port for the Base Station.", "Port Selection Error", MessageBoxButtons.OK);
                return;
            }
            else
            {
                // TODO: Prompt to Calibrate Base Station Color Sensors


                chargeSessions = new ArrayList();   // initialize charge sessions list

                // TODO: populate cars list from database
                // temp: generate list manually
                cars.Add(new Car("car1", "1111"));
                cars.Add(new Car("car2", "2222"));
                cars.Add(new Car("car3", "3333"));
                // Send list of authorized cars to Base Station
                foreach (Car c in cars)
                {

                }
            }
        }

        // Send a string command to the Base Station
        private bool sendCommand(string cmd)
        {
            if (!serialPort1.IsOpen) return false;
            else
            {
                //char[] buff = new char[1];
                //buff[0] = cmd;
                serialPort1.Write("[" + cmd + " ]");
                return true;
            }
        }

        private void monitorButton_Click(object sender, EventArgs e)
        {
            MonitoringForm monitorForm = new MonitoringForm();
            monitorForm.Show();
        }

    }
}
