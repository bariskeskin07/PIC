void interrupt() {
  if (TMR1IF_bit) {    // TMRIF biti kontrol ediliyor (kesme oluþtu mu?)
    PORTB = ~PORTB;    // PORTB konum deðiþtirir
    TMR1H = 0xFF;      // TMR1H ön deðeri
    TMR1L = 0xFE;      // TMR1L ön deðeri
    TMR1IF_bit = 0;    // TMR1IF sýfýrlandý
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;         // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISB = 0;           // PORTB çýkýþ yapýldý
  PORTB = 0xFF;        // PORTB ayarlandý

  TMR1H = 0xFF;        // TMR1H ön deðeri yüklendi
  TMR1L = 0xFE;        // TMR1L ön deðeri yüklendi
  T1CON  = 0x87;       // TMR1 8bit, sayýcý, prescaler 00 = 1
  INTCON = 0xC0;       // GIE, PEIE bitleri set edildi
  TMR1IE_bit = 1;      // TMRO kesmesi aktif edildi

  while(1)
  {
  }

}