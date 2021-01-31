// TMR3 kullanýlmasýnýn sebebi, USB donanýmýnýn TMR1 zamanlayýcýsýna
// müdahele etmesidir. Yani USB donanýmý ile TMR1 kullanýmý sýkýntýlý oluyor.

#include "built_in.h"
#include "USBdsc.c"

#define   servo1        PORTD.RD0
#define   servo2        PORTD.RD1
#define   servo3        PORTD.RD2
#define   servo4        PORTD.RD3
#define   servo5        PORTD.RD4
#define   servo6        PORTD.RD5
#define   servo7        PORTD.RD6
#define   servo8        PORTD.RD7

// LCD module connections
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;
// End LCD module connections

char txt1[] = "HiKKO USB HID V1";
char txt2[] = "MikroC & 18F4550";

//char cnt;
char usb_motor = 1;
char usb_hiz = 1;
char usb_poz = 0;
unsigned poz;

unsigned char readbuff[64] absolute 0x500;
unsigned char writebuff[64] absolute 0x540;

const int rc_poz_limit = 12500;      // PWM Window for servo = 2.5 ms x 8 = 20 ms
//const int ticks4minimum = 3500;      // PWM High for Minimum Position = 0.7 ms
const int rc_poz_min = 2300;       // PWM High for Center Position = 1.5 ms
//const int ticks4maximum = 12300;     // PWM High for Maximum Position = 2.3 ms
//const int ticks4center = 3500;  //7426;


unsigned servo_pwm[8] = {rc_poz_min, rc_poz_min, rc_poz_min,
                         rc_poz_min, rc_poz_min, rc_poz_min,
                         rc_poz_min, rc_poz_min};
unsigned short servo_idx = 0;
bit servo1_on;
bit servo2_on;
bit servo3_on;
bit servo4_on;
bit servo5_on;
bit servo6_on;
bit servo7_on;
bit servo8_on;
bit flag_phase;
unsigned rc_poz_interrupt = 53035;

void interrupt()
{
   USB_Interrupt_Proc();
   if (pir2.tmr3if)
   {
      if (!flag_phase)
      {
         if (servo_idx == 0 && servo1_on) servo1 = 1;
         if (servo_idx == 1 && servo2_on) servo2 = 1;
         if (servo_idx == 2 && servo3_on) servo3 = 1;
         if (servo_idx == 3 && servo4_on) servo4 = 1;
         if (servo_idx == 4 && servo5_on) servo5 = 1;
         if (servo_idx == 5 && servo6_on) servo6 = 1;
         if (servo_idx == 6 && servo7_on) servo7 = 1;
         if (servo_idx == 7 && servo8_on) servo8 = 1;
         rc_poz_interrupt = 65535 - servo_pwm[servo_idx];
         tmr3h = hi(rc_poz_interrupt);
         tmr3l = lo(rc_poz_interrupt);

      }
      if (flag_phase)
      {
         if (servo_idx == 0 && servo1_on) servo1 = 0;
         if (servo_idx == 1 && servo2_on) servo2 = 0;
         if (servo_idx == 2 && servo3_on) servo3 = 0;
         if (servo_idx == 3 && servo4_on) servo4 = 0;
         if (servo_idx == 4 && servo5_on) servo5 = 0;
         if (servo_idx == 5 && servo6_on) servo6 = 0;
         if (servo_idx == 6 && servo7_on) servo7 = 0;
         if (servo_idx == 7 && servo8_on) servo8 = 0;
         rc_poz_interrupt = 65535 - rc_poz_limit + servo_pwm[servo_idx];
         tmr3h = hi(rc_poz_interrupt);
         tmr3l = lo(rc_poz_interrupt);
         if (++servo_idx > 7) servo_idx = 0;
      }
      flag_phase = !flag_phase;
      pir2.TMR3IF = 0;
   }
}

void init()
{
    INTCON2 = 0XF5;
    INTCON3 = 0XC0;

    RCON.IPEN = 0;
    PIE1 = 0;
    PIE2 = 0;
    PIR1 = 0;
    PIR2 = 0;

    ADCON0 = 0;
    ADCON1 |= 0x0A;
    ADCON2 = 0;
    CMCON  |= 7;

    trisd = 0;
    portd = 0;

    trisb = 0xff;
    portb = 0;

    delay_ms(300);

    tmr3h = hi(rc_poz_interrupt);
    tmr3l = lo(rc_poz_interrupt);
    pie2.TMR3IE = 1;
    t3con.TMR3ON = 1;
    INTCON.GIE = 1;
    INTCON.PEIE = 1;

    flag_phase = 0;
    servo1_on = 1;
    servo2_on = 1;
    servo3_on = 1;
    servo4_on = 1;
    servo5_on = 1;
    servo6_on = 1;
    servo7_on = 1;
    servo8_on = 1;
    
    servo1 = 0;
    servo2 = 0;
    servo3 = 0;
    servo4 = 0;
    servo5 = 0;
    servo6 = 0;
    servo7 = 0;
    servo8 = 0;

    Lcd_Init();
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 1, txt1);
    Lcd_Out(2, 1, txt2);

    HID_Enable(&readbuff,&writebuff);

    servo_pwm[0] = 2300;
    servo_pwm[1] = 2300;
    servo_pwm[2] = 2300;
    servo_pwm[3] = 2300;
    servo_pwm[4] = 2300;
    servo_pwm[5] = 2300;
    servo_pwm[6] = 2300;
    servo_pwm[7] = 2300;
}

void pozisyon(unsigned short motor_no, unsigned poz, unsigned short hiz)
{
    unsigned short i;
    while(servo_pwm[motor_no] < poz)
    {
       servo_pwm[motor_no]++;
       for(i = 0; i < hiz; i++) delay_us(100);
    }
    while(servo_pwm[motor_no] > poz)
    {
       servo_pwm[motor_no]--;
       for(i = 0; i < hiz; i++) delay_us(100);
    }
}

void main() {

    init();
    delay_ms(500);

    while(1)
    {
          while(!HID_Read());

          usb_motor = readbuff[0];
          usb_poz = readbuff[1];
          usb_hiz = readbuff[2];

          poz = (55,56 * usb_poz) + 2300;     // (12300 - 2300) = 10000
                                               // 10000 / 180 = 55,56
                                               // poz = (55,56 * açý) + derece

          pozisyon((usb_motor - 1), poz, usb_hiz);
          
/*readbuff[1] = 0x55;                  // motor iþlem tamam.
          for(cnt=0; cnt < 4; cnt++)
             writebuff[cnt]=readbuff[cnt];
          while(!HID_Write(&writebuff,4));*/
    }
}