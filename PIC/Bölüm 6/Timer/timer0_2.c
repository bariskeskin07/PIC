void interrupt() {
  if (TMR0IF_bit) {    // Her 4 butona basýp-býrakma da, yani logicstate
    PORTB = ~PORTB;    // komponentinin 4 kere 1 'den 0 'a (düþen kenar)
    TMR0L = 0xFE;      // alýnmasýnda bir kesme oluþur.
    TMR0H = 0xFF;      //
    TMR0IF_bit = 0;    // TMR0IF sýfýrlandý
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;         // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISB = 0;           // PORTB çýkýþ yapýldý
  PORTB = 0xFF;        // PORTB ayarlandý

  TMR0L = 0xFE;        // TMR0L ön deðeri yüklendi
  TMR0H = 0xFF;        // TMR0H ön deðeri yüklendi
  T0CON  = 0xF0;       // TMR0 16bit modunda, sayýcý prescaler 000 = 2
  INTCON = 0xC0;       // GIE, PEIE bitleri set edildi
  TMR0IE_bit = 1;      // TMRO kesmesi aktif edildi

  while(1)
  {
  }

}