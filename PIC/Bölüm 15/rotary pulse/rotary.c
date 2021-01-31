#define RotaryEncoder portb    // Rotary Encoder ile PIC18F4550 ba�lant�s�

char Encoder, oldEncoder;      // global
unsigned sayac, tmp;           // de�i�kenler
char txt[5];                   // tan�mlan�yor

// LCD module ba�lant�lar�
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
// End LCD module ba�lant�lar�

void init()
{
   ADCON1 |= 0x0F;             // AN pinleri dijital I/O yap�land�r�ld�
   CMCON  |= 7;                // Comparators (kar��la�t�r�c�lar) pasif edildi
   LCD_Init();                 // LCD display yap�land�r�ld�
   LCD_Cmd(_LCD_CURSOR_OFF);   // imleci gizle
   RotaryEncoder = 0;          // Portun ilk durumu s�f�rlan�yor.
   trisb = 0x03;               // Rotary Encoder portu giri� yap�ld�
   Encoder = 0x03;             // Rotary encoder'in de�erini tutan de�i�kene ilk de�er veriliyor.
   sayac = 0;                  // sayac de�eri s�f�rlan�yor.
   Lcd_Out(1, 1, "Sayac:");
}

void main()
{
     init();
     while(1)
     {
          oldEncoder = Encoder;     // yeni de�er eski de�ere y�kleniyor
          tmp = sayac;              // 2 byte'l�k sayac desimale d�n��t�r�l�yor
          WordToStr(tmp, txt);      // decimale d�n��t�r�l�n de�er text'e �evriliyor
          Lcd_Out(2, 1, txt);       // sayac de�eri LCD'de g�r�nt�leniyor
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