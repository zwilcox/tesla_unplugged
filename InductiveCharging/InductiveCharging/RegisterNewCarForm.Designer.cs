namespace InductiveCharging
{
    partial class RegisterNewCarForm
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
            this.registerNewFlowLayoutPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.radioIDLabel = new System.Windows.Forms.Label();
            this.radioIDTextBox = new System.Windows.Forms.TextBox();
            this.registerPadLabel = new System.Windows.Forms.Label();
            this.flowLayoutPanel2 = new System.Windows.Forms.FlowLayoutPanel();
            this.registerCarButton = new System.Windows.Forms.Button();
            this.registerCarCancelButton = new System.Windows.Forms.Button();
            this.registerPadMessageLabel = new System.Windows.Forms.Label();
            this.registerNewFlowLayoutPanel.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.flowLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // registerNewFlowLayoutPanel
            // 
            this.registerNewFlowLayoutPanel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.registerNewFlowLayoutPanel.Controls.Add(this.flowLayoutPanel1);
            this.registerNewFlowLayoutPanel.Controls.Add(this.registerPadLabel);
            this.registerNewFlowLayoutPanel.Controls.Add(this.flowLayoutPanel2);
            this.registerNewFlowLayoutPanel.Controls.Add(this.registerPadMessageLabel);
            this.registerNewFlowLayoutPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.registerNewFlowLayoutPanel.Location = new System.Drawing.Point(12, 12);
            this.registerNewFlowLayoutPanel.Name = "registerNewFlowLayoutPanel";
            this.registerNewFlowLayoutPanel.Size = new System.Drawing.Size(194, 251);
            this.registerNewFlowLayoutPanel.TabIndex = 0;
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.flowLayoutPanel1.Controls.Add(this.radioIDLabel);
            this.flowLayoutPanel1.Controls.Add(this.radioIDTextBox);
            this.flowLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(191, 25);
            this.flowLayoutPanel1.TabIndex = 4;
            // 
            // radioIDLabel
            // 
            this.radioIDLabel.AutoSize = true;
            this.radioIDLabel.Location = new System.Drawing.Point(3, 6);
            this.radioIDLabel.Margin = new System.Windows.Forms.Padding(3, 6, 3, 0);
            this.radioIDLabel.Name = "radioIDLabel";
            this.radioIDLabel.Size = new System.Drawing.Size(58, 13);
            this.radioIDLabel.TabIndex = 5;
            this.radioIDLabel.Text = "Radio ID:  ";
            // 
            // radioIDTextBox
            // 
            this.radioIDTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.radioIDTextBox.Location = new System.Drawing.Point(77, 3);
            this.radioIDTextBox.Margin = new System.Windows.Forms.Padding(13, 3, 3, 3);
            this.radioIDTextBox.Name = "radioIDTextBox";
            this.radioIDTextBox.Size = new System.Drawing.Size(93, 20);
            this.radioIDTextBox.TabIndex = 6;
            // 
            // registerPadLabel
            // 
            this.registerPadLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.registerPadLabel.AutoSize = true;
            this.registerPadLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.registerPadLabel.Location = new System.Drawing.Point(15, 41);
            this.registerPadLabel.Margin = new System.Windows.Forms.Padding(3, 10, 3, 0);
            this.registerPadLabel.Name = "registerPadLabel";
            this.registerPadLabel.Size = new System.Drawing.Size(167, 40);
            this.registerPadLabel.TabIndex = 1;
            this.registerPadLabel.Text = "Enter Vehicle ID and Radio ID and click OK.";
            this.registerPadLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // flowLayoutPanel2
            // 
            this.flowLayoutPanel2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.flowLayoutPanel2.Controls.Add(this.registerCarButton);
            this.flowLayoutPanel2.Controls.Add(this.registerCarCancelButton);
            this.flowLayoutPanel2.Location = new System.Drawing.Point(3, 84);
            this.flowLayoutPanel2.Name = "flowLayoutPanel2";
            this.flowLayoutPanel2.Size = new System.Drawing.Size(191, 29);
            this.flowLayoutPanel2.TabIndex = 6;
            // 
            // registerCarButton
            // 
            this.registerCarButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.registerCarButton.Location = new System.Drawing.Point(3, 3);
            this.registerCarButton.Name = "registerCarButton";
            this.registerCarButton.Size = new System.Drawing.Size(75, 23);
            this.registerCarButton.TabIndex = 0;
            this.registerCarButton.Text = "OK";
            this.registerCarButton.UseVisualStyleBackColor = true;
            this.registerCarButton.Click += new System.EventHandler(this.registerColorButton_Click);
            // 
            // registerCarCancelButton
            // 
            this.registerCarCancelButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.registerCarCancelButton.Location = new System.Drawing.Point(111, 3);
            this.registerCarCancelButton.Margin = new System.Windows.Forms.Padding(30, 3, 3, 3);
            this.registerCarCancelButton.Name = "registerCarCancelButton";
            this.registerCarCancelButton.Size = new System.Drawing.Size(75, 23);
            this.registerCarCancelButton.TabIndex = 5;
            this.registerCarCancelButton.Text = "Cancel";
            this.registerCarCancelButton.UseVisualStyleBackColor = true;
            this.registerCarCancelButton.Click += new System.EventHandler(this.registerCarCancelButton_Click);
            // 
            // registerPadMessageLabel
            // 
            this.registerPadMessageLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.registerPadMessageLabel.AutoSize = true;
            this.registerPadMessageLabel.Location = new System.Drawing.Point(46, 126);
            this.registerPadMessageLabel.Margin = new System.Windows.Forms.Padding(3, 10, 3, 0);
            this.registerPadMessageLabel.Name = "registerPadMessageLabel";
            this.registerPadMessageLabel.Size = new System.Drawing.Size(105, 13);
            this.registerPadMessageLabel.TabIndex = 2;
            this.registerPadMessageLabel.Text = "This is for messages.";
            // 
            // RegisterNewCarForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(220, 275);
            this.Controls.Add(this.registerNewFlowLayoutPanel);
            this.Name = "RegisterNewCarForm";
            this.Text = "Register New Car";
            this.registerNewFlowLayoutPanel.ResumeLayout(false);
            this.registerNewFlowLayoutPanel.PerformLayout();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            this.flowLayoutPanel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.FlowLayoutPanel registerNewFlowLayoutPanel;
        private System.Windows.Forms.Label registerPadLabel;
        private System.Windows.Forms.Button registerCarButton;
        private System.Windows.Forms.Label registerPadMessageLabel;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Label radioIDLabel;
        private System.Windows.Forms.TextBox radioIDTextBox;
        private System.Windows.Forms.Button registerCarCancelButton;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2;

    }
}