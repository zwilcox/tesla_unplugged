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
    public partial class MainForm : Form
    {
        public string megaComPort;
        private string[] portsList;

        public MainForm()
        {
            InitializeComponent();
            getComPorts();
        }

        private void exitButton_Click(object sender, EventArgs e)
        {
            // TODO: turn off all charging pads
            this.Close();
        }

        private void systemTestsButton_Click(object sender, EventArgs e)
        {
            TestForm tests = new TestForm();
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
    }
}
