namespace Lab2
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
            this.ArbitratySlider = new System.Windows.Forms.TrackBar();
            this.SliderHeader = new System.Windows.Forms.Label();
            this.SliderValue = new System.Windows.Forms.Label();
            this.MainTabControl = new System.Windows.Forms.TabControl();
            this.UITab = new System.Windows.Forms.TabPage();
            this.DiagTab = new System.Windows.Forms.TabPage();
            this.DiagnosticsTable = new System.Windows.Forms.TableLayoutPanel();
            this.TestInternetConnectoin = new System.Windows.Forms.Button();
            this.InternetResponse = new System.Windows.Forms.Label();
            this.TestServerConnection = new System.Windows.Forms.Button();
            this.ServerResponse = new System.Windows.Forms.Label();
            this.AppLogTab = new System.Windows.Forms.TabPage();
            this.LogConsole = new System.Windows.Forms.RichTextBox();
            this.SendSliderOutput = new System.Windows.Forms.Label();
            this.SendSliderValue = new System.Windows.Forms.Button();
            this.ReceiveSliderValue = new System.Windows.Forms.Button();
            this.ReceiveSliderOutput = new System.Windows.Forms.Label();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)(this.ArbitratySlider)).BeginInit();
            this.MainTabControl.SuspendLayout();
            this.UITab.SuspendLayout();
            this.DiagTab.SuspendLayout();
            this.DiagnosticsTable.SuspendLayout();
            this.AppLogTab.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ArbitratySlider
            // 
            this.ArbitratySlider.BackColor = System.Drawing.Color.BlanchedAlmond;
            this.ArbitratySlider.LargeChange = 0;
            this.ArbitratySlider.Location = new System.Drawing.Point(9, 19);
            this.ArbitratySlider.Name = "ArbitratySlider";
            this.ArbitratySlider.Size = new System.Drawing.Size(392, 45);
            this.ArbitratySlider.SmallChange = 0;
            this.ArbitratySlider.TabIndex = 0;
            this.ArbitratySlider.ValueChanged += new System.EventHandler(this.ArbitratySlider_ValueChanged);
            this.ArbitratySlider.KeyUp += new System.Windows.Forms.KeyEventHandler(this.ArbitratySlider_KeyUp);
            this.ArbitratySlider.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ArbitratySlider_MouseDown);
            this.ArbitratySlider.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ArbitratySlider_MouseUp);
            // 
            // SliderHeader
            // 
            this.SliderHeader.AutoSize = true;
            this.SliderHeader.Location = new System.Drawing.Point(6, 3);
            this.SliderHeader.Name = "SliderHeader";
            this.SliderHeader.Size = new System.Drawing.Size(65, 13);
            this.SliderHeader.TabIndex = 1;
            this.SliderHeader.Text = "Slider value:";
            // 
            // SliderValue
            // 
            this.SliderValue.AutoSize = true;
            this.SliderValue.Location = new System.Drawing.Point(77, 3);
            this.SliderValue.Name = "SliderValue";
            this.SliderValue.Size = new System.Drawing.Size(42, 13);
            this.SliderValue.TabIndex = 2;
            this.SliderValue.Text = "VALUE";
            // 
            // MainTabControl
            // 
            this.MainTabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.MainTabControl.Controls.Add(this.UITab);
            this.MainTabControl.Controls.Add(this.DiagTab);
            this.MainTabControl.Controls.Add(this.AppLogTab);
            this.MainTabControl.Location = new System.Drawing.Point(12, 12);
            this.MainTabControl.Name = "MainTabControl";
            this.MainTabControl.SelectedIndex = 0;
            this.MainTabControl.Size = new System.Drawing.Size(415, 237);
            this.MainTabControl.TabIndex = 3;
            // 
            // UITab
            // 
            this.UITab.Controls.Add(this.tableLayoutPanel1);
            this.UITab.Controls.Add(this.SliderHeader);
            this.UITab.Controls.Add(this.SliderValue);
            this.UITab.Controls.Add(this.ArbitratySlider);
            this.UITab.Location = new System.Drawing.Point(4, 22);
            this.UITab.Name = "UITab";
            this.UITab.Padding = new System.Windows.Forms.Padding(3);
            this.UITab.Size = new System.Drawing.Size(407, 211);
            this.UITab.TabIndex = 0;
            this.UITab.Text = "Slider";
            this.UITab.UseVisualStyleBackColor = true;
            // 
            // DiagTab
            // 
            this.DiagTab.Controls.Add(this.DiagnosticsTable);
            this.DiagTab.Location = new System.Drawing.Point(4, 22);
            this.DiagTab.Name = "DiagTab";
            this.DiagTab.Size = new System.Drawing.Size(407, 211);
            this.DiagTab.TabIndex = 2;
            this.DiagTab.Text = "Diagnostics";
            this.DiagTab.UseVisualStyleBackColor = true;
            // 
            // DiagnosticsTable
            // 
            this.DiagnosticsTable.ColumnCount = 2;
            this.DiagnosticsTable.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.DiagnosticsTable.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.DiagnosticsTable.Controls.Add(this.TestInternetConnectoin, 0, 0);
            this.DiagnosticsTable.Controls.Add(this.InternetResponse, 1, 0);
            this.DiagnosticsTable.Controls.Add(this.TestServerConnection, 0, 1);
            this.DiagnosticsTable.Controls.Add(this.ServerResponse, 1, 1);
            this.DiagnosticsTable.Dock = System.Windows.Forms.DockStyle.Fill;
            this.DiagnosticsTable.Location = new System.Drawing.Point(0, 0);
            this.DiagnosticsTable.Name = "DiagnosticsTable";
            this.DiagnosticsTable.RowCount = 3;
            this.DiagnosticsTable.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.DiagnosticsTable.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.DiagnosticsTable.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 49F));
            this.DiagnosticsTable.Size = new System.Drawing.Size(407, 211);
            this.DiagnosticsTable.TabIndex = 0;
            // 
            // TestInternetConnectoin
            // 
            this.TestInternetConnectoin.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TestInternetConnectoin.Location = new System.Drawing.Point(3, 3);
            this.TestInternetConnectoin.Name = "TestInternetConnectoin";
            this.TestInternetConnectoin.Size = new System.Drawing.Size(197, 24);
            this.TestInternetConnectoin.TabIndex = 0;
            this.TestInternetConnectoin.Text = "Test Internet Connection";
            this.TestInternetConnectoin.UseVisualStyleBackColor = true;
            this.TestInternetConnectoin.Click += new System.EventHandler(this.TestInternetConnectoin_Click);
            // 
            // InternetResponse
            // 
            this.InternetResponse.AutoSize = true;
            this.InternetResponse.Location = new System.Drawing.Point(206, 0);
            this.InternetResponse.Name = "InternetResponse";
            this.InternetResponse.Size = new System.Drawing.Size(82, 13);
            this.InternetResponse.TabIndex = 1;
            this.InternetResponse.Text = "Not yet tested...";
            // 
            // TestServerConnection
            // 
            this.TestServerConnection.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TestServerConnection.Location = new System.Drawing.Point(3, 33);
            this.TestServerConnection.Name = "TestServerConnection";
            this.TestServerConnection.Size = new System.Drawing.Size(197, 24);
            this.TestServerConnection.TabIndex = 2;
            this.TestServerConnection.Text = "Test Server Connection";
            this.TestServerConnection.UseVisualStyleBackColor = true;
            this.TestServerConnection.Click += new System.EventHandler(this.TestServerConnection_Click);
            // 
            // ServerResponse
            // 
            this.ServerResponse.AutoSize = true;
            this.ServerResponse.Location = new System.Drawing.Point(206, 30);
            this.ServerResponse.Name = "ServerResponse";
            this.ServerResponse.Size = new System.Drawing.Size(79, 13);
            this.ServerResponse.TabIndex = 3;
            this.ServerResponse.Text = "Not yet tested..";
            // 
            // AppLogTab
            // 
            this.AppLogTab.Controls.Add(this.LogConsole);
            this.AppLogTab.Location = new System.Drawing.Point(4, 22);
            this.AppLogTab.Name = "AppLogTab";
            this.AppLogTab.Padding = new System.Windows.Forms.Padding(3);
            this.AppLogTab.Size = new System.Drawing.Size(407, 211);
            this.AppLogTab.TabIndex = 1;
            this.AppLogTab.Text = "Log";
            this.AppLogTab.UseVisualStyleBackColor = true;
            // 
            // LogConsole
            // 
            this.LogConsole.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LogConsole.Location = new System.Drawing.Point(3, 3);
            this.LogConsole.Name = "LogConsole";
            this.LogConsole.ReadOnly = true;
            this.LogConsole.Size = new System.Drawing.Size(401, 205);
            this.LogConsole.TabIndex = 0;
            this.LogConsole.Text = "";
            this.LogConsole.WordWrap = false;
            // 
            // SendSliderOutput
            // 
            this.SendSliderOutput.AutoSize = true;
            this.SendSliderOutput.Dock = System.Windows.Forms.DockStyle.Left;
            this.SendSliderOutput.Location = new System.Drawing.Point(99, 0);
            this.SendSliderOutput.Name = "SendSliderOutput";
            this.SendSliderOutput.Size = new System.Drawing.Size(73, 32);
            this.SendSliderOutput.TabIndex = 3;
            this.SendSliderOutput.Text = "Not yet sent...";
            this.SendSliderOutput.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // SendSliderValue
            // 
            this.SendSliderValue.Location = new System.Drawing.Point(3, 3);
            this.SendSliderValue.Name = "SendSliderValue";
            this.SendSliderValue.Size = new System.Drawing.Size(90, 23);
            this.SendSliderValue.TabIndex = 4;
            this.SendSliderValue.Text = "Send value";
            this.SendSliderValue.UseVisualStyleBackColor = true;
            this.SendSliderValue.Click += new System.EventHandler(this.SendSliderValue_Click);
            // 
            // ReceiveSliderValue
            // 
            this.ReceiveSliderValue.Location = new System.Drawing.Point(3, 35);
            this.ReceiveSliderValue.Name = "ReceiveSliderValue";
            this.ReceiveSliderValue.Size = new System.Drawing.Size(90, 23);
            this.ReceiveSliderValue.TabIndex = 5;
            this.ReceiveSliderValue.Text = "Recieve value";
            this.ReceiveSliderValue.UseVisualStyleBackColor = true;
            this.ReceiveSliderValue.Click += new System.EventHandler(this.ReceiveSliderValue_Click);
            // 
            // ReceiveSliderOutput
            // 
            this.ReceiveSliderOutput.AutoSize = true;
            this.ReceiveSliderOutput.Dock = System.Windows.Forms.DockStyle.Left;
            this.ReceiveSliderOutput.Location = new System.Drawing.Point(99, 32);
            this.ReceiveSliderOutput.Name = "ReceiveSliderOutput";
            this.ReceiveSliderOutput.Size = new System.Drawing.Size(94, 33);
            this.ReceiveSliderOutput.TabIndex = 6;
            this.ReceiveSliderOutput.Text = "Not yet received...";
            this.ReceiveSliderOutput.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 24.1206F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 75.87939F));
            this.tableLayoutPanel1.Controls.Add(this.SendSliderValue, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.ReceiveSliderOutput, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.SendSliderOutput, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.ReceiveSliderValue, 0, 1);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(6, 70);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(398, 65);
            this.tableLayoutPanel1.TabIndex = 7;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(439, 261);
            this.Controls.Add(this.MainTabControl);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "Lab 2 by WW";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.ArbitratySlider)).EndInit();
            this.MainTabControl.ResumeLayout(false);
            this.UITab.ResumeLayout(false);
            this.UITab.PerformLayout();
            this.DiagTab.ResumeLayout(false);
            this.DiagnosticsTable.ResumeLayout(false);
            this.DiagnosticsTable.PerformLayout();
            this.AppLogTab.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TrackBar ArbitratySlider;
        private System.Windows.Forms.Label SliderHeader;
        private System.Windows.Forms.Label SliderValue;
        private System.Windows.Forms.TabControl MainTabControl;
        private System.Windows.Forms.TabPage UITab;
        private System.Windows.Forms.TabPage DiagTab;
        private System.Windows.Forms.TabPage AppLogTab;
        private System.Windows.Forms.RichTextBox LogConsole;
        private System.Windows.Forms.TableLayoutPanel DiagnosticsTable;
        private System.Windows.Forms.Button TestInternetConnectoin;
        private System.Windows.Forms.Label InternetResponse;
        private System.Windows.Forms.Button TestServerConnection;
        private System.Windows.Forms.Label ServerResponse;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Button SendSliderValue;
        private System.Windows.Forms.Label ReceiveSliderOutput;
        private System.Windows.Forms.Label SendSliderOutput;
        private System.Windows.Forms.Button ReceiveSliderValue;
    }
}

