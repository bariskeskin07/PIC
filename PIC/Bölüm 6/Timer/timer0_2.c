void interrupt() {
  if (TMR0IF_bit) {    // Her 4 butona bas�p-b�rakma da, yani logicstate
    PORTB = ~PORTB;    // komponentinin 4 kere 1 'den 0 'a (d��en kenar)
    TMR0L = 0xFE;      // al�nmas�nda bir kesme olu�ur.
    TMR0H = 0xFF;      //
    TMR0IF_bit = 0;    // TMR0IF s�f�rland�
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;         // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISB = 0;           // PORTB ��k�� yap�ld�
  PORTB = 0xFF;        // PORTB ayarland�

  TMR0L = 0xFE;        // TMR0L �n de�eri y�klendi
  TMR0H = 0xFF;        // TMR0H �n de�eri y�klendi
  T0CON  = 0xF0;       // TMR0 16bit modunda, say�c� prescaler 000 = 2
  INTCON = 0xC0;       // GIE, PEIE bitleri set edildi
  TMR0IE_bit = 1;      // TMRO kesmesi aktif edildi

  while(1)
  {
  }

}