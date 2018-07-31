using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Microsoft.IoT.Lightning.Providers;
using Windows.Devices;


// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace Lightning_Test_Wider
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            this.Loaded += MainPage_Loaded;
        }

        private void MainPage_Loaded(object sender, RoutedEventArgs e)
        {
            //check if the Lighning drivers are detected by the application
            if (LightningProvider.IsLightningEnabled)
            {
                //Set the default provider of control devices to be from the lightning drivers
                LowLevelDevicesController.DefaultProvider = LightningProvider.GetAggregateProvider();
                //tell the user that the drivers were detected
                LightningDriverStatus.Text = "Enabled";
            }
            else
            {
                //tell the user that the drivers were not detected
                LightningDriverStatus.Text = "Not Enabled";
            }
        }
    }
}
