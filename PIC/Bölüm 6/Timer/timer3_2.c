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

unsigned cnt, rc0_buton;
char txt[7];           // txt isimli 7 byte char tipi dizi de�i�ken

void interrupt() {
  if (PIR2.TMR3IF) {   // TMR3IF biti kontrol ediliyor (kesme olu�tu mu?)
    cnt++;             // cnt de�i�keninin i�eri�ini 1 art�r
    TMR3H = 0xFF;      // TMR3H ve TMR3L kaydedici �iftine �n de�er
    TMR3L = 0xFE;      // y�klendi (0xFFFE = 65534)
    PIR2.TMR3IF = 0;   // TMR3IF s�f�rland�
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;         // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISC = 0xFF;        // PORTC giri� yap�ld�
  PORTC = 0xFF;        // PORTC ayarland�

  cnt = 0;             // cnt kesme de�i�keni s�f�rland�
  rc0_buton = 0;       // RC0 'a ba�l� butona bas��� sayan de�i�ken s�f�rland�
  TMR3H = 0xFF;        // TMR3H = 0x0B
  TMR3L = 0xFE;        // TMR3L = 0xDC

  T3CON  = 0x23;       // TMR3 16bit say�c�, prescaler 00 = 1
  INTCON = 0xC0;       // GIE ve PEIE biti set edildi
  PIE2.TMR3IE = 1;     // TMR3 kesmesi aktif edildi
  
  Lcd_Init();                          // LCD ba�lant�lar� yap�land�r�ld�
  Lcd_Cmd(_LCD_CURSOR_OFF);            // LCD imleci ekrandan kald�r�ld�
  Lcd_Cmd(_LCD_CLEAR);                 // LCD ekran� silindi
  Lcd_Out(1, 1, "RC0 buton:");        // 1. sat�r, 1. s�tuna text yazd�r�ld�
  Lcd_Out(2, 1, "Kesme:");            // 2. sat�r, 1. s�tuna text yazd�r�ld�

  while(1)
  {
    if (!portc.rc0)                    // RC0 butonuna bas�ld� m�?
    {
      rc0_buton++;                     // de�i�keni bir art�r
      while (!portc.rc0);              // butona bas�� b�rak�lana kadar bekle
    }
    IntToStr((rc0_buton - 1), txt);    // rc0_buton de�i�kenini stringe d�nder
    LCD_Out(1, 11, txt);                // LCD displaye g�nder
    
    IntToStr(cnt, txt);                // cnt de�i�keni stringe d�n��t�r�lerek,
    LCD_Out(2, 11, txt);                // txt isimli de�i�kene aktar�ld� ve LCD
  }                                    // ekran�n 2. sat�r, 8. s�tunundan
                                       // itibaren yazd�r�ld�
}