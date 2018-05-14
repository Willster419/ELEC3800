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
using System.IO;
using System.Xml;

namespace Lab2
{
    public partial class MainForm : Form
    {

        private bool from_mouse = false;
        private const string serverRoot = "http://memes.relhaxmodpack.com/SchoolProjects/ELEC3800_WebApp/";
        private const string saved_settings_file = "http://memes.relhaxmodpack.com/SchoolProjects/ELEC3800_WebApp/sliderValue.txt";
        private const string send_value_script = "http://memes.relhaxmodpack.com/SchoolProjects/ELEC3800_WebApp/set_scrollbar_value.php";
        private const string recieve_value_script = "http://memes.relhaxmodpack.com/SchoolProjects/ELEC3800_WebApp/read_scrollbar_value.php";
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

        private void SendSliderValue_Click(object sender, EventArgs e)
        {
            WriteToLog(string.Format("Sending slider value of {0} to the server", ArbitratySlider.Value));
            SendSliderOutput.Text = "Sending...";
            SendSliderOutput.ForeColor = Color.Orange;
            using (WebClient client = new WebClient())
            {
                client.DownloadStringCompleted += OnSendSliderValueComplete;
                client.DownloadStringAsync(new Uri(send_value_script + "?wrVal=" + ArbitratySlider.Value));
            }
        }

        private void OnSendSliderValueComplete(object sender, DownloadStringCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                WriteToLog(e.Error.ToString());
                SendSliderOutput.Text = "Failed";
                SendSliderOutput.ForeColor = Color.Red;
            }
            else
            {
                WriteToLog("success");
                SendSliderOutput.Text = "Success";
                SendSliderOutput.ForeColor = Color.Green;
            }
        }

        private void ReceiveSliderValue_Click(object sender, EventArgs e)
        {
            WriteToLog(string.Format("Receiveing slider value of {0} to the server", ArbitratySlider.Value));
            ReceiveSliderOutput.Text = "Recieving...";
            ReceiveSliderOutput.ForeColor = Color.Orange;
            using (WebClient client = new WebClient())
            {
                client.DownloadStringCompleted += OnRecieveSliderValueComplete;
                client.DownloadStringAsync(new Uri(recieve_value_script));
            }
        }

        private void OnRecieveSliderValueComplete(object sender, DownloadStringCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                WriteToLog(e.Error.ToString());
                ReceiveSliderOutput.Text = "Failed";
                ReceiveSliderOutput.ForeColor = Color.Red;
            }
            else
            {
                //parse the resulted value
                //if reading the one value in a text document, the below would work
                //int recieved_value = int.Parse(e.Result);
                XmlDocument doc = new XmlDocument();
                try
                {
                    doc.LoadXml(e.Result);
                }
                catch(XmlException ex)
                {
                    WriteToLog(ex.ToString());
                    ReceiveSliderOutput.Text = "Failed to parse xml";
                    return;
                }
                XmlNode node = doc.SelectSingleNode("/html/body/p/xml/scrollbarValue");
                string node_value = node.InnerText.Trim();
                float recieved_value_float = float.Parse(node_value);
                int recieved_value = (int)recieved_value_float;
                WriteToLog(string.Format("connection success, value recieved was {0}",recieved_value));
                ReceiveSliderOutput.Text = string.Format("Recieved value {0}", recieved_value);
                if(recieved_value >= 0 && recieved_value <= ArbitratySlider.Maximum)
                {
                    WriteToLog("recieved value withen required ammount!");
                    ReceiveSliderOutput.ForeColor = Color.Green;
                    ArbitratySlider.Value = recieved_value;
                }
                else
                {
                    WriteToLog("recieved value was not within the required ammount!");
                    ReceiveSliderOutput.ForeColor = Color.Red;
                }
            }
        }

        #region Util methods
        private void MainForm_Load(object sender, EventArgs e)
        {
            WriteToLog("/--------------------------------------------------------------------\\");
            WriteToLog("On application Load");
            UpdateValues();
        }

        //write output to log
        //couldbe used in the future to incorporate a log file
        private void WriteToLog(string value)
        {
            string dateTimeFormat = string.Format("{0:yyyy-MM-dd:HH-mm-ss}", DateTime.Now);
            LogConsole.AppendText(string.Format("{0}     {1}{2}", dateTimeFormat, value, "\n"));
            File.AppendAllText("Lab2.log", string.Format("{0}     {1}{2}", dateTimeFormat, value, "\n"));
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            WriteToLog("On application close");
            WriteToLog("\\--------------------------------------------------------------------/");
        }
        #endregion
    }
}
