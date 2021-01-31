using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace pc_usb_veri_girisi
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

        private void usbHidPort1_OnSpecifiedDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Hikko USB HID (PIC18F4550) Cihazı bağlandı!";
        }

        private void usbHidPort1_OnDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz bağlandı!";
        }

        private void usbHidPort1_OnSpecifiedDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " USB HID (PIC18F4550) Cihazı çıkarıldı!";
        }

        private void usbHidPort1_OnDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz çıkarıldı!";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            usbHidPort1.VendorId = 1234;
            usbHidPort1.ProductId = 4321;
            usbHidPort1.CheckDevicePresent();
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
                byte i = 0, porte = 0x00;
                foreach (byte myData in args.data)
                {
                    usb_gelen[i++] = myData;
                }
                if (usb_gelen[3] == 1)
                {
                    label5.BackColor = Color.Red;
                    porte = Convert.ToByte(porte | 0x01);
                }
                else
                {
                    label5.BackColor = Color.LightSkyBlue;
                }
                label5.Text = "RE0 : " + Convert.ToString(usb_gelen[3]);
                label7.Text = porte.ToString("X2");
                if (usb_gelen[4] == 1)
                {
                    label6.BackColor = Color.Red;
                    porte = Convert.ToByte(porte | 0x02);
                }
                else
                {
                    label6.BackColor = Color.LightSkyBlue;
                }
                label6.Text = "RE1 : " + Convert.ToString(usb_gelen[4]);
                label7.Text = "0X" + porte.ToString("X2");
            }
        }

    }
}
