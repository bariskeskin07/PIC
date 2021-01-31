void interrupt() {
  if (TMR1IF_bit) {    // TMRIF biti kontrol ediliyor (kesme olu�tu mu?)
    PORTB = ~PORTB;    // PORTB konum de�i�tirir
    TMR1H = 0xFF;      // TMR1H �n de�eri
    TMR1L = 0xFE;      // TMR1L �n de�eri
    TMR1IF_bit = 0;    // TMR1IF s�f�rland�
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;         // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISB = 0;           // PORTB ��k�� yap�ld�
  PORTB = 0xFF;        // PORTB ayarland�

  TMR1H = 0xFF;        // TMR1H �n de�eri y�klendi
  TMR1L = 0xFE;        // TMR1L �n de�eri y�klendi
  T1CON  = 0x87;       // TMR1 8bit, say�c�, prescaler 00 = 1
  INTCON = 0xC0;       // GIE, PEIE bitleri set edildi
  TMR1IE_bit = 1;      // TMRO kesmesi aktif edildi

  while(1)
  {
  }

}