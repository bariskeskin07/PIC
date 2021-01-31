unsigned cnt;

void interrupt() {
  if (TMR0IF_bit) {
    cnt++;             // Her kesmede cnt i�eri�i 1 art�r�ld�
    TMR0L  = 158;
    TMR0IF_bit = 0;    // TMR0IF s�f�rland�
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;         // Comparators (kar��la�t�r�c�lar) pasif edildi

  cnt = 0;             // cnt de�i�keni s�f�rland�
  TRISB = 0;           // PORTB ��k�� yap�ld�
  PORTB = 0xFF;        // PORTB ayarland�

  T0CON  = 0xC7;       // TMR0 8bit modunda, assign prescaler to TMR0
  INTCON = 0xC0;       // GIE, PEIE bitleri set edildi
  TMR0IE_bit = 1;      // TMRO kesmesi aktif edildi

  do {
    if (cnt >= 100) {
      PORTB = ~PORTB;  // PORTB LED leri konum de�i�tirdi
      cnt = 0;         // cnt resetlendi
    }
  } while(1);          // endless loop
}