unsigned cnt;

void interrupt() {
  if (TMR1IF_bit) {    // TMRIF biti kontrol ediliyor (kesme olu�tu mu?)
    cnt++;             // cnt de�i�keninin i�eri�ini 1 art�r
    TMR1H = 0xE7;      // TMR1 = 59286 = 0xE796
    TMR1L = 0x96;      // TMR1H = 0xE7, TMR1L = 0x96
    TMR1IF_bit = 0;    // TMR1IF s�f�rland�
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;         // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISB = 0;           // PORTB ��k�� yap�ld�
  PORTB = 0xFF;        // PORTB ayarland�

  cnt = 0;
  TMR1H = 0xE7;        // TMR1L �n de�eri y�klendi
  TMR1L = 0x96;        // TMR1H �n de�eri y�klendi
  T1CON  = 0xFD;       // TMR1 16bit modunda, zamanlay�c�, prescaler 11 = 8
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