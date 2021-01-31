using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace usb_rc_kontrol
{
    public partial class Form1 : Form
    {
        byte[] rc_motor_poz = new byte[15];
        byte motor_no = 0;
        byte rc_hiz;
        byte rc_poz;
        sbyte derece;
        TextBox[] mytextbox = new TextBox[8];
        Label[] mylabel = new Label[30];
        Button[] mybutton = new Button[8];
        TrackBar[] mytrackbar = new TrackBar[8];
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

        private void usb_gonder(byte motor_no, byte pozisyon, byte hiz)
        {
            byte[] dizi = new byte[64]; //new byte[usbHidPort1.SpecifiedDevice.OutputReportLength + 1];
            dizi[0] = 0;
            dizi[1] = motor_no;
            dizi[2] = pozisyon;
            dizi[3] = hiz;
            if (usbHidPort1.SpecifiedDevice != null) {
                usbHidPort1.SpecifiedDevice.SendData(dizi); }
            else {
                MessageBox.Show("USB cihaz hazır değil, cihazı takınız!.. "); }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            byte i;
            toolStripStatusLabel1.Text = "USB && RC Motor Kontrol Kartı bağlı değil!..";
            for (i = 1; i < 9; i++)  rc_motor_poz[i] = 0;
            motor_no = 0;
            textBox10.Text = "0" + Convert.ToString(Convert.ToChar(176));
            textBox11.Text = "-90" + Convert.ToString(Convert.ToChar(176));

            mytextbox[0] = textBox1; mytextbox[1] = textBox2;
            mytextbox[2] = textBox3; mytextbox[3] = textBox4;
            mytextbox[4] = textBox5; mytextbox[5] = textBox6;
            mytextbox[6] = textBox7; mytextbox[7] = textBox8;
            for (i = 0; i < 8; i++) mytextbox[i].Text = "0" + 
                Convert.ToString(Convert.ToChar(176));

            mybutton[0] = button1; mybutton[1] = button2;
            mybutton[2] = button3; mybutton[3] = button4;
            mybutton[4] = button5; mybutton[5] = button6;
            mybutton[6] = button7; mybutton[7] = button8;

            mylabel[0] = label10; mylabel[1] = label11;
            mylabel[2] = label12; mylabel[3] = label13;
            mylabel[4] = label14; mylabel[5] = label15;
            mylabel[6] = label16; mylabel[7] = label17;
            for (i = 0; i < 8; i++) mylabel[i].Text = "-90" + 
                Convert.ToString(Convert.ToChar(176));

            mytrackbar[0] = trackBar1; mytrackbar[1] = trackBar2;
            mytrackbar[2] = trackBar3; mytrackbar[3] = trackBar4;
            mytrackbar[4] = trackBar5; mytrackbar[5] = trackBar6;
            mytrackbar[6] = trackBar7; mytrackbar[7] = trackBar8;

            usbHidPort1.VendorId = 0x1111;
            usbHidPort1.ProductId = 0x2222;
            usbHidPort1.CheckDevicePresent();
        }

        private void usbHidPort1_OnSpecifiedDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " USB && RC Motor Kontrol Kartı hazır!";
        }

        private void usbHidPort1_OnDeviceArrived(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz bağlandı!";
        }

        private void usbHidPort1_OnSpecifiedDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " USB && RC Motor Kontrol Kartı çıkarıldı!..";
        }

        private void usbHidPort1_OnDeviceRemoved(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = " Herhangi bir USB Cihaz çıkarıldı!..";
        }

        private void trackBar9_Scroll(object sender, EventArgs e)
        {
            textBox9.Text = Convert.ToString(trackBar9.Value);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            for (byte i = 0; i < 8; i++)
            {
                if (sender == mybutton[i])
                {
                    mybutton[i].BackColor = Color.Red;
                    motor_no = Convert.ToByte(i + 1);
                    textBox10.Text = Convert.ToString(rc_motor_poz[motor_no]) +
                        Convert.ToString(Convert.ToChar(176));
                }
                else mybutton[i].BackColor = Color.WhiteSmoke;
            }
            rc_poz = Convert.ToByte(rc_motor_poz[motor_no]);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (motor_no > 0)
            {
                rc_motor_poz[motor_no] += Convert.ToByte(trackBar9.Value);
                if (rc_motor_poz[motor_no] > 180) rc_motor_poz[motor_no] = 180;
                textBox10.Text = Convert.ToString(rc_motor_poz[motor_no]) + 
                    Convert.ToString(Convert.ToChar(176));
                textBox11.Text = Convert.ToString(rc_motor_poz[motor_no] - 90) +
                    Convert.ToString(Convert.ToChar(176));
            }
            else MessageBox.Show("RC Motor seçiniz!");
            rc_hiz = Convert.ToByte(trackBar9.Value);
            rc_poz = Convert.ToByte(rc_motor_poz[motor_no]);
            usb_gonder(motor_no, rc_poz, rc_hiz);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            rc_motor_poz[motor_no] -= Convert.ToByte(trackBar9.Value);
            if (rc_motor_poz[motor_no] < 1 | rc_motor_poz[motor_no] > 240) rc_motor_poz[motor_no] = 0;
            textBox10.Text = Convert.ToString(rc_motor_poz[motor_no]) + 
                Convert.ToString(Convert.ToChar(176));
            rc_hiz = Convert.ToByte(trackBar9.Value);
            rc_poz = Convert.ToByte(rc_motor_poz[motor_no]);
            usb_gonder(motor_no, rc_poz, rc_hiz);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            for (byte i = 0; i < 8; i++)
            {
                if (sender == mytrackbar[i])
                {
                    mytextbox[i].Text = Convert.ToString(mytrackbar[i].Value * 10) +
                       Convert.ToString(Convert.ToChar(176));
                    derece = Convert .ToSByte (mytrackbar[i].Value * 10 - 90);
                    mylabel[i].Text = Convert.ToString(derece);
                    motor_no = Convert.ToByte(i + 1);
                    rc_poz = Convert.ToByte(mytrackbar[i].Value * 10);
                }
            }
            rc_hiz = Convert.ToByte(trackBar9.Value);
            usb_gonder(motor_no, rc_poz, rc_hiz);
        }
    }
}
