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
            dataManager = new DataManager();
        }

        private void exitButton_Click(object sender, EventArgs e)
        {
            // TODO: turn off all charging pads
            this.Close();
        }

        private void systemTestsButton_Click(object sender, EventArgs e)
        {
            // TODO: verify port is selected
            TestForm tests = new TestForm(ref dataManager);
            tests.Show();
        }

        private void getComPorts()
        {
            portsList = System.IO.Ports.SerialPort.GetPortNames();
            portsComboBox.Items.AddRange(portsList);
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

        private void portsComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            Properties.Settings.Default.selectedPort = portsComboBox.Text;
            Properties.Settings.Default.Save();
        }

        private void startButton_Click(object sender, EventArgs e)
        {
            // TODO: Verify port selected
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
}
