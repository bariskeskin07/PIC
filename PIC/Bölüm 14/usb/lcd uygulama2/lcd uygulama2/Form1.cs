using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace lcd_uygulama2
{
    public partial class Form1 : Form
    {
        const byte text_kod = 0xAB;
        const byte komut_kod = 0xAD;
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
            usbHidPort1.VendorId = 1234;
            usbHidPort1.ProductId = 4321;
            usbHidPort1.CheckDevicePresent();
            textBox1.MaxLength = 16;
        }

        private void usbHidPort1_OnSpecifiedDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " USB HID (PIC18F4550) ve LCD Cihazı bağlandı!";
        }

        private void usbHidPort1_OnSpecifiedDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " USB HID (PIC18F4550) ve LCD Cihazı çıkarıldı!";
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
            byte[] dizi = new byte[usbHidPort1.SpecifiedDevice.OutputReportLength + 1];
            dizi[0] = 0;
            dizi[1] = text_kod;
            dizi[2] = Convert.ToByte(textBox1.Text.Length);
            for (int i = 0; i < textBox1.Text.Length; i++)
            {
                dizi[i + 3] = Convert.ToByte(textBox1.Text[i]);
            }

            if (textBox1.Text.Length < usbHidPort1.SpecifiedDevice.OutputReportLength)
            {
                int j;
                for (j = textBox1.Text.Length + 3; j < usbHidPort1.SpecifiedDevice.OutputReportLength; j++)
                {
                    dizi[j] = 0xFF;
                }
            }

            if (usbHidPort1.SpecifiedDevice != null)
                usbHidPort1.SpecifiedDevice.SendData(dizi);
        }

        private void usb_komut_gonder(byte komut)
        {
            byte[] dizi = new byte[usbHidPort1.SpecifiedDevice.OutputReportLength + 1];
            dizi[0] = 0;
            dizi[1] = komut_kod;
            dizi[2] = komut;
            for (int i = 3; i < 64; i++) dizi[i] = 0xFF;
            if (usbHidPort1.SpecifiedDevice != null)
                usbHidPort1.SpecifiedDevice.SendData(dizi);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(1);    // LCD ekranını sil
        }

        private void button3_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(2);    // 1. satır
        }

        private void button4_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(3);    // 2. satır
        }

        private void button5_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(4);    // kürsör off
        }

        private void button6_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(5);    // kürsörü altı çizgili yap
        }

        private void button7_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(6);    // kürsörü blink yap
        }

        private void button8_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(7);    // kürsörü sola kaydır
        }

        private void button9_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(8);    // kürsörü sağa kaydır
        }

        private void button10_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(9);    // LCD ekranı sola kaydır
        }

        private void button11_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(10);   // LCD ekran açık
        }

        private void button12_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(11);   // LCD ekran kapalı
        }

        private void button13_Click(object sender, EventArgs e)
        {
            usb_komut_gonder(12);   // LCD ekranı sağa kaydır
        }
    }
}
