unsigned cnt;

void interrupt() {
  if (TMR2IF_bit) {    // TMR2IF biti kontrol ediliyor (kesme oluştu mu?)
    cnt++;             // cnt değişkeninin içeriğini 1 artır
    TMR2 = 6;          // TMR2 = 6
    TMR2IF_bit = 0;    // TMR1IF sıfırlandı
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yapılandırıldı
  CMCON  |= 7;         // Comparators (karşılaştırıcılar) pasif edildi

  TRISB = 0;           // PORTB çıkış yapıldı
  PORTB = 0xFF;        // PORTB ayarlandı

  cnt = 0;
  TMR2 = 6;            // TMR2 ön değeri yüklendi
  T2CON  = 0x05;       // TMR2 8bit zamanlayıcı, prescaler 01 = 4
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