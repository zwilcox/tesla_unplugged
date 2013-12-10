namespace InductiveCharging
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea4 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend4 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series7 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series8 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.mainFlowLayoutPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.titleLabel = new System.Windows.Forms.Label();
            this.tableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.systemTestsButton = new System.Windows.Forms.Button();
            this.exitPanel = new System.Windows.Forms.Panel();
            this.exitButton = new System.Windows.Forms.Button();
            this.stopPanel = new System.Windows.Forms.Panel();
            this.manualButton = new System.Windows.Forms.Button();
            this.manualPanel = new System.Windows.Forms.Panel();
            this.stopButton = new System.Windows.Forms.Button();
            this.startPanel = new System.Windows.Forms.Panel();
            this.startButton = new System.Windows.Forms.Button();
            this.flowLayoutPanel2 = new System.Windows.Forms.FlowLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.portsComboBox = new System.Windows.Forms.ComboBox();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.redChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.inductiveDataSet1 = new InductiveCharging.INDUCTIVEDataSet();
            this.carsTableAdapter1 = new InductiveCharging.INDUCTIVEDataSetTableAdapters.CarsTableAdapter();
            this.chargeSessionsTableAdapter1 = new InductiveCharging.INDUCTIVEDataSetTableAdapters.ChargeSessionsTableAdapter();
            this.pad1AmpsTableAdapter1 = new InductiveCharging.INDUCTIVEDataSetTableAdapters.pad1AmpsTableAdapter();
            this.pad1VoltsTableAdapter1 = new InductiveCharging.INDUCTIVEDataSetTableAdapters.pad1VoltsTableAdapter();
            this.pad2AmpsTableAdapter1 = new InductiveCharging.INDUCTIVEDataSetTableAdapters.pad2AmpsTableAdapter();
            this.pad2VoltsTableAdapter1 = new InductiveCharging.INDUCTIVEDataSetTableAdapters.pad2VoltsTableAdapter();
            this.pad3AmpsTableAdapter1 = new InductiveCharging.INDUCTIVEDataSetTableAdapters.pad3AmpsTableAdapter();
            this.pad3VoltsTableAdapter1 = new InductiveCharging.INDUCTIVEDataSetTableAdapters.pad3VoltsTableAdapter();
            this.tableAdapterManager1 = new InductiveCharging.INDUCTIVEDataSetTableAdapters.TableAdapterManager();
            this.mainFlowLayoutPanel.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel.SuspendLayout();
            this.panel1.SuspendLayout();
            this.exitPanel.SuspendLayout();
            this.stopPanel.SuspendLayout();
            this.manualPanel.SuspendLayout();
            this.startPanel.SuspendLayout();
            this.flowLayoutPanel2.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.redChart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.inductiveDataSet1)).BeginInit();
            this.SuspendLayout();
            // 
            // mainFlowLayoutPanel
            // 
            this.mainFlowLayoutPanel.Controls.Add(this.tableLayoutPanel1);
            this.mainFlowLayoutPanel.Location = new System.Drawing.Point(12, 12);
            this.mainFlowLayoutPanel.Name = "mainFlowLayoutPanel";
            this.mainFlowLayoutPanel.Size = new System.Drawing.Size(1037, 401);
            this.mainFlowLayoutPanel.TabIndex = 0;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 39.3617F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 60.6383F));
            this.tableLayoutPanel1.Controls.Add(this.titleLabel, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.flowLayoutPanel1, 1, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 15.12195F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 84.87805F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1034, 398);
            this.tableLayoutPanel1.TabIndex = 2;
            // 
            // titleLabel
            // 
            this.titleLabel.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.titleLabel.AutoSize = true;
            this.titleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.titleLabel.Location = new System.Drawing.Point(61, 0);
            this.titleLabel.Name = "titleLabel";
            this.titleLabel.Size = new System.Drawing.Size(283, 37);
            this.titleLabel.TabIndex = 0;
            this.titleLabel.Text = "Inductive Charging";
            // 
            // tableLayoutPanel
            // 
            this.tableLayoutPanel.ColumnCount = 2;
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 49.65517F));
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.34483F));
            this.tableLayoutPanel.Controls.Add(this.panel1, 0, 2);
            this.tableLayoutPanel.Controls.Add(this.exitPanel, 1, 1);
            this.tableLayoutPanel.Controls.Add(this.stopPanel, 0, 1);
            this.tableLayoutPanel.Controls.Add(this.manualPanel, 1, 0);
            this.tableLayoutPanel.Controls.Add(this.startPanel, 0, 0);
            this.tableLayoutPanel.Controls.Add(this.flowLayoutPanel2, 1, 2);
            this.tableLayoutPanel.Location = new System.Drawing.Point(3, 63);
            this.tableLayoutPanel.Name = "tableLayoutPanel";
            this.tableLayoutPanel.RowCount = 3;
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 109F));
            this.tableLayoutPanel.Size = new System.Drawing.Size(400, 311);
            this.tableLayoutPanel.TabIndex = 1;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.systemTestsButton);
            this.panel1.Location = new System.Drawing.Point(3, 205);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(192, 100);
            this.panel1.TabIndex = 3;
            // 
            // systemTestsButton
            // 
            this.systemTestsButton.BackColor = System.Drawing.Color.Lime;
            this.systemTestsButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.systemTestsButton.Location = new System.Drawing.Point(31, 29);
            this.systemTestsButton.Name = "systemTestsButton";
            this.systemTestsButton.Size = new System.Drawing.Size(135, 36);
            this.systemTestsButton.TabIndex = 0;
            this.systemTestsButton.Text = "Test Mode";
            this.systemTestsButton.UseVisualStyleBackColor = false;
            this.systemTestsButton.Click += new System.EventHandler(this.systemTestsButton_Click);
            // 
            // exitPanel
            // 
            this.exitPanel.Controls.Add(this.exitButton);
            this.exitPanel.Location = new System.Drawing.Point(201, 104);
            this.exitPanel.Name = "exitPanel";
            this.exitPanel.Size = new System.Drawing.Size(196, 95);
            this.exitPanel.TabIndex = 2;
            // 
            // exitButton
            // 
            this.exitButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.exitButton.Location = new System.Drawing.Point(32, 29);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(135, 36);
            this.exitButton.TabIndex = 0;
            this.exitButton.Text = "Exit";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.exitButton_Click);
            // 
            // stopPanel
            // 
            this.stopPanel.Controls.Add(this.manualButton);
            this.stopPanel.Location = new System.Drawing.Point(3, 104);
            this.stopPanel.Name = "stopPanel";
            this.stopPanel.Size = new System.Drawing.Size(192, 95);
            this.stopPanel.TabIndex = 2;
            // 
            // manualButton
            // 
            this.manualButton.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.manualButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.manualButton.Location = new System.Drawing.Point(31, 29);
            this.manualButton.Name = "manualButton";
            this.manualButton.Size = new System.Drawing.Size(135, 36);
            this.manualButton.TabIndex = 0;
            this.manualButton.Text = "Manual Mode";
            this.manualButton.UseVisualStyleBackColor = false;
            // 
            // manualPanel
            // 
            this.manualPanel.Controls.Add(this.stopButton);
            this.manualPanel.Location = new System.Drawing.Point(201, 3);
            this.manualPanel.Name = "manualPanel";
            this.manualPanel.Size = new System.Drawing.Size(196, 95);
            this.manualPanel.TabIndex = 2;
            // 
            // stopButton
            // 
            this.stopButton.BackColor = System.Drawing.Color.Red;
            this.stopButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stopButton.Location = new System.Drawing.Point(32, 29);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(135, 36);
            this.stopButton.TabIndex = 0;
            this.stopButton.Text = "Stop System";
            this.stopButton.UseVisualStyleBackColor = false;
            // 
            // startPanel
            // 
            this.startPanel.Controls.Add(this.startButton);
            this.startPanel.Location = new System.Drawing.Point(3, 3);
            this.startPanel.Name = "startPanel";
            this.startPanel.Size = new System.Drawing.Size(192, 95);
            this.startPanel.TabIndex = 1;
            // 
            // startButton
            // 
            this.startButton.BackColor = System.Drawing.Color.Lime;
            this.startButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.startButton.Location = new System.Drawing.Point(31, 29);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(135, 36);
            this.startButton.TabIndex = 0;
            this.startButton.Text = "Start System";
            this.startButton.UseVisualStyleBackColor = false;
            this.startButton.Click += new System.EventHandler(this.startButton_Click);
            // 
            // flowLayoutPanel2
            // 
            this.flowLayoutPanel2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.flowLayoutPanel2.Controls.Add(this.label1);
            this.flowLayoutPanel2.Controls.Add(this.portsComboBox);
            this.flowLayoutPanel2.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.flowLayoutPanel2.Location = new System.Drawing.Point(209, 215);
            this.flowLayoutPanel2.Name = "flowLayoutPanel2";
            this.flowLayoutPanel2.Size = new System.Drawing.Size(179, 83);
            this.flowLayoutPanel2.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(3, 0);
            this.label1.Margin = new System.Windows.Forms.Padding(3, 0, 3, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(171, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "Base Station Com Port";
            // 
            // portsComboBox
            // 
            this.portsComboBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.portsComboBox.FormattingEnabled = true;
            this.portsComboBox.Location = new System.Drawing.Point(28, 38);
            this.portsComboBox.Name = "portsComboBox";
            this.portsComboBox.Size = new System.Drawing.Size(121, 21);
            this.portsComboBox.TabIndex = 0;
            this.portsComboBox.SelectedIndexChanged += new System.EventHandler(this.portsComboBox_SelectedIndexChanged);
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.redChart);
            this.flowLayoutPanel1.Location = new System.Drawing.Point(409, 3);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.tableLayoutPanel1.SetRowSpan(this.flowLayoutPanel1, 2);
            this.flowLayoutPanel1.Size = new System.Drawing.Size(622, 392);
            this.flowLayoutPanel1.TabIndex = 2;
            // 
            // redChart
            // 
            chartArea4.Area3DStyle.Enable3D = true;
            chartArea4.Name = "ChartArea1";
            this.redChart.ChartAreas.Add(chartArea4);
            legend4.Name = "Legend1";
            this.redChart.Legends.Add(legend4);
            this.redChart.Location = new System.Drawing.Point(3, 3);
            this.redChart.Name = "redChart";
            series7.ChartArea = "ChartArea1";
            series7.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series7.Legend = "Legend1";
            series7.Name = "Red Car";
            series8.ChartArea = "ChartArea1";
            series8.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series8.Legend = "Legend1";
            series8.Name = "Blue Car";
            this.redChart.Series.Add(series7);
            this.redChart.Series.Add(series8);
            this.redChart.Size = new System.Drawing.Size(619, 389);
            this.redChart.TabIndex = 0;
            this.redChart.Text = "redChart";
            // 
            // inductiveDataSet1
            // 
            this.inductiveDataSet1.DataSetName = "INDUCTIVEDataSet";
            this.inductiveDataSet1.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // carsTableAdapter1
            // 
            this.carsTableAdapter1.ClearBeforeFill = true;
            // 
            // chargeSessionsTableAdapter1
            // 
            this.chargeSessionsTableAdapter1.ClearBeforeFill = true;
            // 
            // pad1AmpsTableAdapter1
            // 
            this.pad1AmpsTableAdapter1.ClearBeforeFill = true;
            // 
            // pad1VoltsTableAdapter1
            // 
            this.pad1VoltsTableAdapter1.ClearBeforeFill = true;
            // 
            // pad2AmpsTableAdapter1
            // 
            this.pad2AmpsTableAdapter1.ClearBeforeFill = true;
            // 
            // pad2VoltsTableAdapter1
            // 
            this.pad2VoltsTableAdapter1.ClearBeforeFill = true;
            // 
            // pad3AmpsTableAdapter1
            // 
            this.pad3AmpsTableAdapter1.ClearBeforeFill = true;
            // 
            // pad3VoltsTableAdapter1
            // 
            this.pad3VoltsTableAdapter1.ClearBeforeFill = true;
            // 
            // tableAdapterManager1
            // 
            this.tableAdapterManager1.BackupDataSetBeforeUpdate = false;
            this.tableAdapterManager1.CarsTableAdapter = null;
            this.tableAdapterManager1.ChargeSessionsTableAdapter = null;
            this.tableAdapterManager1.pad1AmpsTableAdapter = null;
            this.tableAdapterManager1.pad1VoltsTableAdapter = this.pad1VoltsTableAdapter1;
            this.tableAdapterManager1.pad2AmpsTableAdapter = this.pad2AmpsTableAdapter1;
            this.tableAdapterManager1.pad2VoltsTableAdapter = this.pad2VoltsTableAdapter1;
            this.tableAdapterManager1.pad3AmpsTableAdapter = this.pad3AmpsTableAdapter1;
            this.tableAdapterManager1.pad3VoltsTableAdapter = this.pad3VoltsTableAdapter1;
            this.tableAdapterManager1.UpdateOrder = InductiveCharging.INDUCTIVEDataSetTableAdapters.TableAdapterManager.UpdateOrderOption.InsertUpdateDelete;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1061, 425);
            this.Controls.Add(this.mainFlowLayoutPanel);
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "Inductive Charging";
            this.mainFlowLayoutPanel.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.exitPanel.ResumeLayout(false);
            this.stopPanel.ResumeLayout(false);
            this.manualPanel.ResumeLayout(false);
            this.startPanel.ResumeLayout(false);
            this.flowLayoutPanel2.ResumeLayout(false);
            this.flowLayoutPanel2.PerformLayout();
            this.flowLayoutPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.redChart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.inductiveDataSet1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.FlowLayoutPanel mainFlowLayoutPanel;
        private System.Windows.Forms.Label titleLabel;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.DataVisualization.Charting.Chart redChart;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button systemTestsButton;
        private System.Windows.Forms.Panel exitPanel;
        private System.Windows.Forms.Button exitButton;
        private System.Windows.Forms.Panel stopPanel;
        private System.Windows.Forms.Button stopButton;
        private System.Windows.Forms.Panel manualPanel;
        private System.Windows.Forms.Button manualButton;
        private System.Windows.Forms.Panel startPanel;
        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox portsComboBox;
        private System.IO.Ports.SerialPort serialPort1;
        private INDUCTIVEDataSet inductiveDataSet1;
        private INDUCTIVEDataSetTableAdapters.CarsTableAdapter carsTableAdapter1;
        private INDUCTIVEDataSetTableAdapters.ChargeSessionsTableAdapter chargeSessionsTableAdapter1;
        private INDUCTIVEDataSetTableAdapters.pad1AmpsTableAdapter pad1AmpsTableAdapter1;
        private INDUCTIVEDataSetTableAdapters.pad1VoltsTableAdapter pad1VoltsTableAdapter1;
        private INDUCTIVEDataSetTableAdapters.pad2AmpsTableAdapter pad2AmpsTableAdapter1;
        private INDUCTIVEDataSetTableAdapters.pad2VoltsTableAdapter pad2VoltsTableAdapter1;
        private INDUCTIVEDataSetTableAdapters.pad3AmpsTableAdapter pad3AmpsTableAdapter1;
        private INDUCTIVEDataSetTableAdapters.pad3VoltsTableAdapter pad3VoltsTableAdapter1;
        private INDUCTIVEDataSetTableAdapters.TableAdapterManager tableAdapterManager1;
    }
}

