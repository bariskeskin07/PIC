#define RotaryEncoder portb    // Rotary Encoder ile PIC18F4550 baðlantýsý

char Encoder, oldEncoder;      // global
unsigned sayac, tmp;           // deðiþkenler
char txt[5];                   // tanýmlanýyor

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
   LCD_Cmd(_LCD_CURSOR_OFF);   // imleci gizle
   RotaryEncoder = 0;          // Portun ilk durumu sýfýrlanýyor.
   trisb = 0x03;               // Rotary Encoder portu giriþ yapýldý
   Encoder = 0x03;             // Rotary encoder'in deðerini tutan deðiþkene ilk deðer veriliyor.
   sayac = 0;                  // sayac deðeri sýfýrlanýyor.
   Lcd_Out(1, 1, "Sayac:");
}

void main()
{
     init();
     while(1)
     {
          oldEncoder = Encoder;     // yeni deðer eski deðere yükleniyor
          tmp = sayac;              // 2 byte'lýk sayac desimale dönüþtürülüyor
          WordToStr(tmp, txt);      // decimale dönüþtürülün deðer text'e çevriliyor
          Lcd_Out(2, 1, txt);       // sayac deðeri LCD'de görüntüleniyor
          if (Encoder == oldEncoder) Encoder = RotaryEncoder & 0x03;
          if (oldEncoder.F1 != Encoder.F0)
          {
              if (oldEncoder.F0 == Encoder.F1) if (sayac < 9999) sayac++;
          }
          if (oldEncoder.F0 != Encoder.F1)
          {
              if (oldEncoder.F1 == Encoder.F0 ) if (sayac > 0) sayac--;
          }
     }
}