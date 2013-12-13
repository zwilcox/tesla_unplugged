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
        DataManager dataManager;


        public MainForm()
        {
            InitializeComponent();
            getComPorts();
            dataManager = new DataManager(inductiveDataSet1, tableAdapterManager1);
            this.FormClosing += MainForm_FormClosing;

            dataManager.currentSession1.TableNewRow += updateChargeSessionDataTable1;
            dataManager.currentSession2.TableNewRow += updateChargeSessionDataTable2;
            dataManager.currentSession3.TableNewRow += updateChargeSessionDataTable3;
            dataManager.currentSession1.TableCleared += updateChargeSessionDataTable1;
            dataManager.currentSession2.TableCleared += updateChargeSessionDataTable2;
            dataManager.currentSession3.TableCleared += updateChargeSessionDataTable3;

            session1Chart.DataSource = dataManager.currentSession1;

            session1Chart.Series["Car"].XValueMember = "carTimestamp";
            session1Chart.Series["Car"].YValueMembers = "carPower";
            session1Chart.Series["Pad 1"].XValueMember = "padTimestamp";
            session1Chart.Series["Pad 1"].YValueMembers = "padPower";
            //session1Chart.ChartAreas[0].AxisX.

            session2Chart.DataSource = dataManager.currentSession2;

            session2Chart.Series["Car"].XValueMember = "carTimestamp";
            session2Chart.Series["Car"].YValueMembers = "carPower";
            session2Chart.Series["Pad 2"].XValueMember = "padTimestamp";
            session2Chart.Series["Pad 2"].YValueMembers = "padPower";

            session3Chart.DataSource = dataManager.currentSession3;

            session3Chart.Series["Car"].XValueMember = "carTimestamp";
            session3Chart.Series["Car"].YValueMembers = "carPower";
            session3Chart.Series["Pad 3"].XValueMember = "padTimestamp";
            session3Chart.Series["Pad 3"].YValueMembers = "padPower";

            session2Chart.DataBind();
            session3Chart.DataBind();
            session1Chart.DataBind();

        }

        private void updateChargeSessionDataTable1(object sender, EventArgs e)
        {
            this.Invoke(new EventHandler(updateChart1));
        }

        private void updateChart1(object sender, EventArgs e)
        {
            session1Chart.DataBind();
        }

        private void updateChargeSessionDataTable2(object sender, EventArgs e)
        {
            this.Invoke(new EventHandler(updateChart2));
        }

        private void updateChart2(object sender, EventArgs e)
        {
            session2Chart.DataBind();
        }

        private void updateChargeSessionDataTable3(object sender, EventArgs e)
        {
            this.Invoke(new EventHandler(updateChart3));
        }

        private void updateChart3(object sender, EventArgs e)
        {
            session3Chart.DataBind();
        }

        // Exit the system and close the application
        private void exitButton_Click(object sender, EventArgs e)
        {
            dataManager.clearBSAuthCarsList();
            dataManager.turnAllPadsOff();
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

            if (Properties.Settings.Default.selectedPort == "")
            {
                MessageBox.Show("Please select a serial port for the Base Station.", "Port Selection Error", MessageBoxButtons.OK);
                return;
            }
            else
            {
                // Prompt to Calibrate Base Station Color Sensors
                if (Properties.Settings.Default.checkForCal && !Properties.Settings.Default.isCalibrated)
                {
                    MessageBox.Show("Please calibrate Base Station before starting system.", "Calibration Needed", MessageBoxButtons.OK);
                }
                else
                {

                    // populate cars list from database
                    dataManager.populateAuthorizedCarsList();

                    // Send list of cars to Base Station
                    dataManager.clearBSAuthCarsList();
                    dataManager.sendAuthCarsToBaseStation();
                    
                    // Disable start button and enable stop button
                    startButton.Enabled = false;
                    startButton.BackColor = Color.LightGray;
                    stopButton.Enabled = true;
                    stopButton.BackColor = Color.Red;
                    
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

        // 
        private void monitorButton_Click(object sender, EventArgs e)
        {
            MonitoringForm monitorForm = new MonitoringForm(inductiveDataSet1, tableAdapterManager1);
            monitorForm.Show();
        }

        // Turn everything off and stop system
        private void stopButton_Click(object sender, EventArgs e)
        {
            dataManager.clearBSAuthCarsList();
            dataManager.turnAllPadsOff();
            startButton.Enabled = true;
            startButton.BackColor = Color.Lime;
            stopButton.Enabled = false;
            stopButton.BackColor = Color.LightGray;

        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            dataManager.clearBSAuthCarsList();
            dataManager.turnAllPadsOff();
        }

    }
}
