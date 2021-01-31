unsigned cnt;

void interrupt() {
  if (TMR0IF_bit) {
    cnt++;             // Her kesmede cnt içeriði 1 artýrýldý
    TMR0L  = 158;
    TMR0IF_bit = 0;    // TMR0IF sýfýrlandý
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;         // Comparators (karþýlaþtýrýcýlar) pasif edildi

  cnt = 0;             // cnt deðiþkeni sýfýrlandý
  TRISB = 0;           // PORTB çýkýþ yapýldý
  PORTB = 0xFF;        // PORTB ayarlandý

  T0CON  = 0xC7;       // TMR0 8bit modunda, assign prescaler to TMR0
  INTCON = 0xC0;       // GIE, PEIE bitleri set edildi
  TMR0IE_bit = 1;      // TMRO kesmesi aktif edildi

  do {
    if (cnt >= 100) {
      PORTB = ~PORTB;  // PORTB LED leri konum deðiþtirdi
      cnt = 0;         // cnt resetlendi
    }
  } while(1);          // endless loop
}