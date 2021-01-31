unsigned cnt;

void interrupt() {
  if (TMR1IF_bit) {    // TMRIF biti kontrol ediliyor (kesme oluþtu mu?)
    cnt++;             // cnt deðiþkeninin içeriðini 1 artýr
    TMR1H = 0xE7;      // TMR1 = 59286 = 0xE796
    TMR1L = 0x96;      // TMR1H = 0xE7, TMR1L = 0x96
    TMR1IF_bit = 0;    // TMR1IF sýfýrlandý
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;         // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISB = 0;           // PORTB çýkýþ yapýldý
  PORTB = 0xFF;        // PORTB ayarlandý

  cnt = 0;
  TMR1H = 0xE7;        // TMR1L ön deðeri yüklendi
  TMR1L = 0x96;        // TMR1H ön deðeri yüklendi
  T1CON  = 0xFD;       // TMR1 16bit modunda, zamanlayýcý, prescaler 11 = 8
  INTCON = 0xC0;       // GIE, PEIE bitleri set edildi
  TMR1IE_bit = 1;      // TMRO kesmesi aktif edildi

  while(1)
  {
     if (cnt >= 100)   // 100 x 10 ms = 1 saniye
     {
        PORTB = ~PORTB;
        cnt = 0;
     }
  }

}