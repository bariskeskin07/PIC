#define klavye          PORTB
#define klavye_tris     TRISB
#define sutun3          RB0
#define sutun2          RB1
#define sutun1          RB2
#define satir1          RB3
#define satir2          RB4
#define kl_int          RB5

unsigned char key;

// LCD module baðlantýlarý
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module baðlantýlarý

void init()
{
   ADCON1 |= 0x0F;             // AN pinleri dijital I/O yapýlandýrýldý
   CMCON  |= 7;                // Comparators (karþýlaþtýrýcýlar) pasif edildi
   LCD_Init();                 // LCD display yapýlandýrýldý
   LCD_CMD(_LCD_CURSOR_OFF);
   LCD_OUT(1,1,"Tusa basiniz!..");
   LCD_CMD(_LCD_SECOND_ROW);
   klavye = 0;
   klavye_tris.sutun1 = 0;
   klavye_tris.sutun2 = 0;
   klavye_tris.sutun3 = 0;
   klavye_tris.satir1 = 1;
   klavye_tris.satir2 = 1;
   klavye_tris.kl_int = 1;
}

void sutun_tara (unsigned short sut1, unsigned short sut2, unsigned short sut3)
{
       klavye.sutun1 = sut1;
       klavye.sutun2 = sut2;
       klavye.sutun3 = sut3;
}

void tarama_yap(unsigned short sat1, unsigned short sat2, unsigned short sut1, unsigned short sut2, unsigned short sut3, char key_in)
{
      sutun_tara(sut1, sut2, sut3);
      while ((!klavye.kl_int) && (klavye.satir1 == sat1) && (klavye.satir2 == sat2))
      {
         LCD_Chr_Cp(key_in);
         key = key_in;
         sutun_tara(0, 0, 0);
         while (!klavye.kl_int);
      }
      sutun_tara(0, 0, 0);
}

void tus()
{
     tarama_yap(0, 0, 0, 1, 1, '1');
     tarama_yap(0, 0, 1, 0, 1, '2');
     tarama_yap(0, 0, 1, 1, 0, '3');
     tarama_yap(0, 1, 0, 1, 1, '4');
     tarama_yap(0, 1, 1, 0, 1, '5');
     tarama_yap(0, 1, 1, 1, 0, '6');
     tarama_yap(1, 0, 0, 1, 1, '7');
     tarama_yap(1, 0, 1, 0, 1, '8');
     tarama_yap(1, 0, 1, 1, 0, '9');
     tarama_yap(1, 1, 0, 1, 1, '*');
     tarama_yap(1, 1, 1, 0, 1, '0');
     tarama_yap(1, 1, 1, 1, 0, '#');
}

void main() {
   init();
   while(1)
   {
       sutun_tara(0, 0, 0);
       while (!klavye.kl_int) tus();
   }
}