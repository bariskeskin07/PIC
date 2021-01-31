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

unsigned cnt, rc0_buton;
char txt[7];           // txt isimli 7 byte char tipi dizi deðiþken

void interrupt() {
  if (PIR2.TMR3IF) {   // TMR3IF biti kontrol ediliyor (kesme oluþtu mu?)
    cnt++;             // cnt deðiþkeninin içeriðini 1 artýr
    TMR3H = 0xFF;      // TMR3H ve TMR3L kaydedici çiftine ön deðer
    TMR3L = 0xFE;      // yüklendi (0xFFFE = 65534)
    PIR2.TMR3IF = 0;   // TMR3IF sýfýrlandý
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;         // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISC = 0xFF;        // PORTC giriþ yapýldý
  PORTC = 0xFF;        // PORTC ayarlandý

  cnt = 0;             // cnt kesme deðiþkeni sýfýrlandý
  rc0_buton = 0;       // RC0 'a baðlý butona basýþý sayan deðiþken sýfýrlandý
  TMR3H = 0xFF;        // TMR3H = 0x0B
  TMR3L = 0xFE;        // TMR3L = 0xDC

  T3CON  = 0x23;       // TMR3 16bit sayýcý, prescaler 00 = 1
  INTCON = 0xC0;       // GIE ve PEIE biti set edildi
  PIE2.TMR3IE = 1;     // TMR3 kesmesi aktif edildi
  
  Lcd_Init();                          // LCD baðlantýlarý yapýlandýrýldý
  Lcd_Cmd(_LCD_CURSOR_OFF);            // LCD imleci ekrandan kaldýrýldý
  Lcd_Cmd(_LCD_CLEAR);                 // LCD ekraný silindi
  Lcd_Out(1, 1, "RC0 buton:");        // 1. satýr, 1. sütuna text yazdýrýldý
  Lcd_Out(2, 1, "Kesme:");            // 2. satýr, 1. sütuna text yazdýrýldý

  while(1)
  {
    if (!portc.rc0)                    // RC0 butonuna basýldý mý?
    {
      rc0_buton++;                     // deðiþkeni bir artýr
      while (!portc.rc0);              // butona basýþ býrakýlana kadar bekle
    }
    IntToStr((rc0_buton - 1), txt);    // rc0_buton deðiþkenini stringe dönder
    LCD_Out(1, 11, txt);                // LCD displaye gönder
    
    IntToStr(cnt, txt);                // cnt deðiþkeni stringe dönüþtürülerek,
    LCD_Out(2, 11, txt);                // txt isimli deðiþkene aktarýldý ve LCD
  }                                    // ekranýn 2. satýr, 8. sütunundan
                                       // itibaren yazdýrýldý
}