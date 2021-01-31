using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace lcd_uygulama1
{
    public partial class Form1 : Form
    {
        const byte text_kod = 0xAB;
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
            toolStripStatusLabel1.Text = "USB Cihazı bağlayınız!..";
            textBox3.MaxLength = 16;
        }

        private void usbHidPort1_OnSpecifiedDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Hikko USB HID (PIC18F4550) Cihazı bağlandı!";
        }

        private void usbHidPort1_OnSpecifiedDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Hikko USB HID (PIC18F4550) Cihazı çıkarıldı!";
        }

        private void usbHidPort1_OnDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz bağlandı!";
        }

        private void usbHidPort1_OnDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz çıkarıldı!";
        }       

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                usbHidPort1.VendorId = Convert.ToInt32(textBox1.Text);
                usbHidPort1.ProductId = Convert.ToInt32(textBox2.Text);
                if ((usbHidPort1.VendorId == 1234) & (usbHidPort1.ProductId == 4321))
                {
                    usbHidPort1.CheckDevicePresent();
                }
                else
                {
                    MessageBox.Show("Yanlış Vendor ID yada Product ID girdiniz!..");
                }
            }
            catch
            {
                MessageBox.Show("Vendor ID ile Product ID girmelisiniz!.. ");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] dizi = new byte[usbHidPort1.SpecifiedDevice.OutputReportLength + 1];
            dizi[0] = 0;
            dizi[1] = text_kod;
            dizi[2] = Convert.ToByte(textBox3.Text.Length);
            for (int i = 0; i < textBox3.Text.Length; i++)
            {
                dizi[i + 3] = Convert.ToByte(textBox3.Text[i]);
            }

            if (textBox1.Text.Length < usbHidPort1.SpecifiedDevice.OutputReportLength)
            {
                int j;
                for (j = textBox3.Text.Length + 3; j < usbHidPort1.SpecifiedDevice.OutputReportLength; j++)
                {
                    dizi[j] = 0xFF;
                }
            }

            if (usbHidPort1.SpecifiedDevice != null)
                usbHidPort1.SpecifiedDevice.SendData(dizi);
        }
    }
}
