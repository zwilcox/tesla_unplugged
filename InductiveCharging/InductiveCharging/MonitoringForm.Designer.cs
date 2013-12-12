namespace InductiveCharging
{
    partial class MonitoringForm
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
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.monitoringLabel = new System.Windows.Forms.Label();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.flowLayoutPanel2 = new System.Windows.Forms.FlowLayoutPanel();
            this.monitoringButton = new System.Windows.Forms.Button();
            this.monitoringCloseButton = new System.Windows.Forms.Button();
            this.flowLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.flowLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.flowLayoutPanel1.Controls.Add(this.tableLayoutPanel1);
            this.flowLayoutPanel1.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(12, 12);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(1113, 689);
            this.flowLayoutPanel1.TabIndex = 0;
            // 
            // monitoringLabel
            // 
            this.monitoringLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.monitoringLabel.AutoSize = true;
            this.monitoringLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.monitoringLabel.Location = new System.Drawing.Point(3, 11);
            this.monitoringLabel.Name = "monitoringLabel";
            this.monitoringLabel.Size = new System.Drawing.Size(292, 26);
            this.monitoringLabel.TabIndex = 0;
            this.monitoringLabel.Text = "Monitoring Charging Stations";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 49.93581F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.06419F));
            this.tableLayoutPanel1.Controls.Add(this.flowLayoutPanel2, 0, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 53F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.34F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1110, 686);
            this.tableLayoutPanel1.TabIndex = 1;
            // 
            // flowLayoutPanel2
            // 
            this.flowLayoutPanel2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.tableLayoutPanel1.SetColumnSpan(this.flowLayoutPanel2, 2);
            this.flowLayoutPanel2.Controls.Add(this.monitoringLabel);
            this.flowLayoutPanel2.Controls.Add(this.monitoringButton);
            this.flowLayoutPanel2.Controls.Add(this.monitoringCloseButton);
            this.flowLayoutPanel2.Location = new System.Drawing.Point(3, 3);
            this.flowLayoutPanel2.Name = "flowLayoutPanel2";
            this.flowLayoutPanel2.Size = new System.Drawing.Size(1104, 47);
            this.flowLayoutPanel2.TabIndex = 0;
            // 
            // monitoringButton
            // 
            this.monitoringButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.monitoringButton.Location = new System.Drawing.Point(328, 3);
            this.monitoringButton.Margin = new System.Windows.Forms.Padding(30, 3, 3, 3);
            this.monitoringButton.Name = "monitoringButton";
            this.monitoringButton.Size = new System.Drawing.Size(147, 42);
            this.monitoringButton.TabIndex = 1;
            this.monitoringButton.Text = "Monitor Cars";
            this.monitoringButton.UseVisualStyleBackColor = true;
            // 
            // monitoringCloseButton
            // 
            this.monitoringCloseButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.monitoringCloseButton.Location = new System.Drawing.Point(1007, 3);
            this.monitoringCloseButton.Margin = new System.Windows.Forms.Padding(529, 3, 3, 3);
            this.monitoringCloseButton.Name = "monitoringCloseButton";
            this.monitoringCloseButton.Size = new System.Drawing.Size(94, 42);
            this.monitoringCloseButton.TabIndex = 2;
            this.monitoringCloseButton.Text = "Close";
            this.monitoringCloseButton.UseVisualStyleBackColor = true;
            // 
            // MonitoringForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1137, 713);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Name = "MonitoringForm";
            this.Text = "MonitoringForm";
            this.flowLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel2.ResumeLayout(false);
            this.flowLayoutPanel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2;
        private System.Windows.Forms.Label monitoringLabel;
        private System.Windows.Forms.Button monitoringButton;
        private System.Windows.Forms.Button monitoringCloseButton;
    }
}