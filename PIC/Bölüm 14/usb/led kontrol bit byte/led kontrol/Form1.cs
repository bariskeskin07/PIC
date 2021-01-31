using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace led_kontrol
{
    public partial class Form1 : Form
    {
        byte sayi = 0;
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
            int x = 20;
            int y = 20;
            for (int i = 0; i < 8; i++)
            {
                Button yenibuton = new Button();
                yenibuton.Name = "yenibuton" + (i + 1).ToString();
                yenibuton.Text = "B" + i;
                this.groupBox4.Controls.Add(yenibuton);
                yenibuton.SetBounds(x, y, 30, 30);
                x += 30;
                //yenibuton.Click += new EventHandler(yenibuton_Click);
            }
        }

        private void usb_gonder(byte veri)
        {
            byte[] dizi = new byte[usbHidPort1.SpecifiedDevice.OutputReportLength + 1];
            dizi[0] = 0;
            dizi[1] = veri;
            for (int i = 2; i < textBox1.Text.Length; i++)
            {
                dizi[i] = 0xFF;
            }
            if (usbHidPort1.SpecifiedDevice != null)
            {
                usbHidPort1.SpecifiedDevice.SendData(dizi);
            }
            else
            {
                MessageBox.Show("USB cihaz hazır değil, cihazı takınız!.. ");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz bağlı değil!..";
            checkBox1.Checked = true;
            checkBox2.Checked = false;
        }

        private void usbHidPort1_OnSpecifiedDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Hikko USB HID (PIC18F4550) Cihazı bağlandı!";
        }

        private void usbHidPort1_OnDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz bağlandı!";
        }

        private void usbHidPort1_OnDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Hikko USB HID (PIC18F4550) Cihazı çıkarıldı!";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                usbHidPort1.VendorId = Convert.ToInt32(textBox1.Text);
                usbHidPort1.ProductId = Convert.ToInt32(textBox2.Text);
                usbHidPort1.CheckDevicePresent();
            }
            catch
            {
                MessageBox.Show("Vendor ID ile Product ID girmelisiniz!.. ");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox3.Text != "")
                {
                    if (checkBox1.Checked)
                        sayi = Byte.Parse(textBox3.Text, System.Globalization.NumberStyles.HexNumber);
                    if (checkBox2.Checked)
                        sayi = Convert.ToByte(textBox3.Text);
                }
                usb_gonder(sayi);
            }
            catch
            {
                MessageBox.Show("Hatalı bir sayı girdiniz!.. Sayı 1 byte olmalı!");
                textBox3.Text = "0";
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked) checkBox2.Checked = false;
            if (checkBox2.Checked) checkBox1.Checked = false;
            textBox3.MaxLength = 2;
            textBox3.Text = "0";
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked) checkBox1.Checked = false;
            if (checkBox1.Checked) checkBox2.Checked = false;
            textBox3.MaxLength = 3;
        }      
    }
}
