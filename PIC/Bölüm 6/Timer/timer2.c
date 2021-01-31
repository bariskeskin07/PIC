unsigned cnt;

void interrupt() {
  if (TMR2IF_bit) {    // TMR2IF biti kontrol ediliyor (kesme olu�tu mu?)
    cnt++;             // cnt de�i�keninin i�eri�ini 1 art�r
    TMR2 = 6;          // TMR2 = 6
    TMR2IF_bit = 0;    // TMR1IF s�f�rland�
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;         // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISB = 0;           // PORTB ��k�� yap�ld�
  PORTB = 0xFF;        // PORTB ayarland�

  cnt = 0;
  TMR2 = 6;            // TMR2 �n de�eri y�klendi
  T2CON  = 0x05;       // TMR2 8bit zamanlay�c�, prescaler 01 = 4
  INTCON = 0xC0;       // GIE, PEIE bitleri set edildi
  TMR2IE_bit = 1;      // TMRO kesmesi aktif edildi

  while(1)
  {
     if (cnt >= 1000)   // 1000 x 1 ms = 1000 ms = 1 sn
     {
        portb++;
        cnt = 0;
     }
  }
  
}