using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;

namespace Lab1
{
    public partial class MainForm : Form
    {

        private bool from_mouse = false;
        private const string serverRoot = "http://memes.relhaxmodpack.com/SchoolProjects/ELEC3800_WebApp/";
        private const string internetTest = "http://google.com";

        //main constructor
        public MainForm()
        {
            InitializeComponent();
        }

        //event that fires on slider movement
        private void ArbitratySlider_ValueChanged(object sender, EventArgs e)
        {
            if(!from_mouse)
            {
                //process changes...
                UpdateValues();
            }
        }

        //event that fires when the slider is chnaged AND the user has finished dragging with the mouse
        private void ArbitratySlider_MouseUp(object sender, MouseEventArgs e)
        {
            //process changes...
            UpdateValues();
            from_mouse = false;
        }

        //event the fires whe nthe slider is changed. use this to determine if it's a one time keyboard click or a mouse event
        private void ArbitratySlider_MouseDown(object sender, MouseEventArgs e)
        {
            from_mouse = true;
            //now the value changed won't run code untill the mouse is back up
            //set the slider directly on where the mouse is
            //can set the value directly becaues from_mouse is still true
            //get a scale value of the x location to the width of the control
            //and apply that scale to the new value based on maximum number of ticks
            float scale = (float)e.X / (float)ArbitratySlider.Size.Width;
            float new_value = ArbitratySlider.Maximum * scale;
            ArbitratySlider.Value = (int)Math.Round(new_value);
        }

        private void UpdateValues()
        {
            WriteToLog(string.Format("on main slider change: value={0}", ArbitratySlider.Value));
            SliderValue.Text = "" + ArbitratySlider.Value;
            if(ArbitratySlider.Value < 3)
            {
                //green
                SliderValue.ForeColor = Color.Green;
            }
            else if (ArbitratySlider.Value >=3 && ArbitratySlider.Value < 7)
            {
                //yellow
                SliderValue.ForeColor = Color.Orange;
            }
            else if (ArbitratySlider.Value >= 7)
            {
                //red
                SliderValue.ForeColor = Color.Red;
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            WriteToLog("On application Load");
            UpdateValues();
        }

        //write output to log
        //couldbe used in the future to incorporate a log file
        private void WriteToLog(string value)
        {
            string dateTimeFormat = string.Format("{0:yyyy-MM-dd:HH-mm-ss}", DateTime.Now);
            LogConsole.AppendText(string.Format("{0}     {1}{2}",dateTimeFormat,value,"\n"));
        }

        private void TestInternetConnectoin_Click(object sender, EventArgs e)
        {
            InternetResponse.Text = "Testing connection...";
            InternetResponse.ForeColor = Color.Orange;
            WriteToLog("Testing internet connection...");
            //actually test the internet conention
            using (WebClient client = new WebClient())
            {
                client.DownloadStringCompleted += OnInternetTestResponse;
                client.DownloadStringAsync(new Uri(internetTest));
            }
        }

        private void OnInternetTestResponse(object sender, DownloadStringCompletedEventArgs e)
        {
            if(e.Error != null)
            {
                //test failed, log exception
                WriteToLog(e.Error.ToString());
                InternetResponse.Text = "Failed, check your internet conenctsion";
                InternetResponse.ForeColor = Color.Red;
            }
            else
            {
                //test success
                InternetResponse.Text = "Success";
                WriteToLog("Internet test success");
                InternetResponse.ForeColor = Color.Green;
            }
        }

        private void TestServerConnection_Click(object sender, EventArgs e)
        {
            ServerResponse.Text = "Testing connection...";
            ServerResponse.ForeColor = Color.Orange;
            WriteToLog("Testing internet connection...");
            //actually test the server conention
            using (WebClient client = new WebClient())
            {
                client.DownloadStringCompleted += OnServerTestResponse;
                client.DownloadStringAsync(new Uri(serverRoot));
            }
        }

        private void OnServerTestResponse(object sender, DownloadStringCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                //test failed, log exception
                WriteToLog(e.Error.ToString());
                ServerResponse.Text = "Failed, check your internet conenctsion";
                ServerResponse.ForeColor = Color.Red;
            }
            else
            {
                //test success
                WriteToLog("Server test success");
                ServerResponse.Text = "Success";
                ServerResponse.ForeColor = Color.Green;
            }
        }

        private void ArbitratySlider_KeyUp(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Left)
            {
                if(ArbitratySlider.Value != 0)
                    ArbitratySlider.Value--;
            }
            else if (e.KeyCode == Keys.Right)
            {
                if (ArbitratySlider.Value != ArbitratySlider.Maximum)
                    ArbitratySlider.Value++;
            }
        }
    }
}
