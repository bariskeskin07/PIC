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
        int sayi = 0;
        bool led_flag1 = false;
        bool led_flag2 = false;
        bool led_flag3 = false;
        bool led_flag4 = false;
        bool led_flag5 = false;
        bool led_flag6 = false;
        bool led_flag7 = false;
        bool led_flag8 = false;
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
                yenibuton.BackColor = Color.Blue;
                yenibuton.Click += new EventHandler(yenibuton_Click);
            }
        }

        private void usb_gonder(byte veri)
        {
            try
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
            }
            catch
            {
                MessageBox.Show("USB cihaz hazır değil, cihazı takınız!.. ");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz bağlı değil!..";
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
                if ((usbHidPort1.VendorId == 4660) & (usbHidPort1.ProductId == 4660))
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

        private void yenibuton_Click(object sender, System.EventArgs e)
        {
            Button yenibuton = sender as Button;
            switch (yenibuton.Name)
            {
                case "yenibuton1":
                    led_flag1 = !led_flag1;
                    if (led_flag1 == true)
                       { yenibuton.BackColor = Color.Red; sayi = sayi | 0x01; }
                    else
                       { yenibuton.BackColor = Color.Blue; sayi = sayi & 0xFE; }
                    break;
                case "yenibuton2":
                    led_flag2 = !led_flag2;
                    if (led_flag2 == true)
                    { yenibuton.BackColor = Color.Red; sayi = sayi | 0x02; }
                    else
                    { yenibuton.BackColor = Color.Blue; sayi = sayi & 0xFD; }
                    break;
                case "yenibuton3":
                    led_flag3 = !led_flag3;
                    if (led_flag3 == true)
                    { yenibuton.BackColor = Color.Red; sayi = sayi | 0x04; }
                    else
                    { yenibuton.BackColor = Color.Blue; sayi = sayi & 0xFB; }
                    break;
                case "yenibuton4":
                    led_flag4 = !led_flag4;
                    if (led_flag4 == true)
                    { yenibuton.BackColor = Color.Red; sayi = sayi | 0x08; }
                    else
                    { yenibuton.BackColor = Color.Blue; sayi = sayi & 0xF7; }
                    break;
                case "yenibuton5":
                    led_flag5 = !led_flag5;
                    if (led_flag5 == true)
                    { yenibuton.BackColor = Color.Red; sayi = sayi | 0x10; }
                    else
                    { yenibuton.BackColor = Color.Blue; sayi = sayi & 0xEF; }
                    break;
                case "yenibuton6":
                    led_flag6 = !led_flag6;
                    if (led_flag6 == true)
                    { yenibuton.BackColor = Color.Red; sayi = sayi | 0x20; }
                    else
                    { yenibuton.BackColor = Color.Blue; sayi = sayi & 0xDF; }
                    break;
                case "yenibuton7":
                    led_flag7 = !led_flag7;
                    if (led_flag7 == true)
                    { yenibuton.BackColor = Color.Red; sayi = sayi | 0x40; }
                    else
                    { yenibuton.BackColor = Color.Blue; sayi = sayi & 0xBF; }
                    break;
                case "yenibuton8":
                    led_flag8 = !led_flag8;
                    if (led_flag8 == true)
                    { yenibuton.BackColor = Color.Red; sayi = sayi | 0x80; }
                    else
                    { yenibuton.BackColor = Color.Blue; sayi = sayi & 0x7F; }
                    break;
            }
            usb_gonder(Convert.ToByte(sayi));
        }

    }
}
