using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace termometre
{
    public partial class Form1 : Form
    {
        protected override void OnHandleCreated(EventArgs e)
        {
            base.OnHandleCreated(e);
            usbHidPort1.RegisterHandle(Handle);
        }

        protected override void WndProc(ref Message m)
        {
            usbHidPort1.ParseMessages(ref m);
            base.WndProc(ref m);
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            label1.Text = "DS18B20 Ölçülen Isı Değeri :";
            label1.Font = new Font("Arial", 20);
            label2.Text = "000.0000" + "  C";
            label1.Font = new Font("Arial", 20);
            toolStripStatusLabel1.Text = " USB && DS18B20 Cihazı bağlı değil!..";
            usbHidPort1.VendorId = 1234;
            usbHidPort1.ProductId = 4321;
            usbHidPort1.CheckDevicePresent();
        }

        private void usbHidPort1_OnSpecifiedDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " USB && DS18B20 Cihazı bağlandı!";
        }

        private void usbHidPort1_OnDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz bağlandı!";
        }

        private void usbHidPort1_OnSpecifiedDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " USB && DS18B20 Cihazı çıkarıldı!";
        }

        private void usbHidPort1_OnDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz çıkarıldı!";
        }

        private void usbHidPort1_OnDataRecieved(object sender, UsbLibrary.DataRecievedEventArgs args)
        {
            if (InvokeRequired)
            {
                try
                {
                    Invoke(new UsbLibrary.DataRecievedEventHandler(usbHidPort1_OnDataRecieved), new object[] { sender, args });
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.ToString());
                }
            }
            else
            {
                byte[] usb_gelen = new byte[usbHidPort1.SpecifiedDevice.OutputReportLength + 1];
                byte i = 0;
                foreach (byte myData in args.data)
                {
                    usb_gelen[i++] = myData;
                }
                label2.Text = Convert.ToString(Convert.ToChar(usb_gelen[1]))
                + Convert.ToString(Convert.ToChar(usb_gelen[2]))
                + Convert.ToString(Convert.ToChar(usb_gelen[3]))
                + Convert.ToString(Convert.ToChar(usb_gelen[4]))
                + Convert.ToString(Convert.ToChar(usb_gelen[5]))
                + Convert.ToString(Convert.ToChar(usb_gelen[6]))
                + Convert.ToString(Convert.ToChar(usb_gelen[7]))
                + " " + Convert.ToString(Convert.ToChar(176)) + "C";
            }
        }
    }
}
