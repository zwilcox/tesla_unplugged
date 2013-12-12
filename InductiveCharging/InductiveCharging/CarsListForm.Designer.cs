namespace InductiveCharging
{
    partial class CarsListForm
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
            this.carsListLabel = new System.Windows.Forms.Label();
            this.carsListBox = new System.Windows.Forms.ListBox();
            this.flowLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.flowLayoutPanel1.Controls.Add(this.carsListLabel);
            this.flowLayoutPanel1.Controls.Add(this.carsListBox);
            this.flowLayoutPanel1.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(12, 12);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(374, 246);
            this.flowLayoutPanel1.TabIndex = 0;
            // 
            // carsListLabel
            // 
            this.carsListLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.carsListLabel.AutoSize = true;
            this.carsListLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.carsListLabel.Location = new System.Drawing.Point(59, 0);
            this.carsListLabel.Name = "carsListLabel";
            this.carsListLabel.Size = new System.Drawing.Size(258, 26);
            this.carsListLabel.TabIndex = 0;
            this.carsListLabel.Text = "Current Cars in Database";
            this.carsListLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // carsListBox
            // 
            this.carsListBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.carsListBox.FormattingEnabled = true;
            this.carsListBox.Location = new System.Drawing.Point(3, 29);
            this.carsListBox.Name = "carsListBox";
            this.carsListBox.Size = new System.Drawing.Size(370, 212);
            this.carsListBox.TabIndex = 1;
            // 
            // CarsListForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(398, 270);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Name = "CarsListForm";
            this.Text = "CarsListForm";
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Label carsListLabel;
        public System.Windows.Forms.ListBox carsListBox;

    }
}