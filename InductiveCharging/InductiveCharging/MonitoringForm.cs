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
    public partial class MonitoringForm : Form
    {

        private INDUCTIVEDataSetTableAdapters.CarsTableAdapter carsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.ChargeSessionsTableAdapter chargeSessionsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad1AmpsTableAdapter pad1AmpsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad1VoltsTableAdapter pad1VoltsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad2AmpsTableAdapter pad2AmpsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad2VoltsTableAdapter pad2VoltsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad3AmpsTableAdapter pad3AmpsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.pad3VoltsTableAdapter pad3VoltsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.carVoltsTableAdapter carVoltsTableAdapter;
        private INDUCTIVEDataSetTableAdapters.carAmpsTableAdapter carAmpsTableAdapter;
        private INDUCTIVEDataSet dataSet;

        public MonitoringForm(INDUCTIVEDataSet data, INDUCTIVEDataSetTableAdapters.TableAdapterManager tableAdapterManager)
        {
            InitializeComponent();
        }

        private void MonitoringForm_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'iNDUCTIVEDataSet.pad3Amps' table. You can move, or remove it, as needed.
            this.pad3AmpsTableAdapter1.Fill(this.iNDUCTIVEDataSet.pad3Amps);
            // TODO: This line of code loads data into the 'iNDUCTIVEDataSet.pad2Amps' table. You can move, or remove it, as needed.
            this.pad2AmpsTableAdapter1.Fill(this.iNDUCTIVEDataSet.pad2Amps);
            // TODO: This line of code loads data into the 'iNDUCTIVEDataSet.pad1Amps' table. You can move, or remove it, as needed.
            this.pad1AmpsTableAdapter1.Fill(this.iNDUCTIVEDataSet.pad1Amps);
            // TODO: This line of code loads data into the 'iNDUCTIVEDataSet.pad3Volts' table. You can move, or remove it, as needed.
            this.pad3VoltsTableAdapter1.Fill(this.iNDUCTIVEDataSet.pad3Volts);
            // TODO: This line of code loads data into the 'iNDUCTIVEDataSet.pad1Volts' table. You can move, or remove it, as needed.
            this.pad1VoltsTableAdapter1.Fill(this.iNDUCTIVEDataSet.pad1Volts);

        }

        private void monitoringCloseButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
