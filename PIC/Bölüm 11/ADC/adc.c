unsigned int adc_sinyal;

void main() {

  ADCON0 = 0x09;             // A/D donan�m birimi aktif edildi
  ADCON1 &= 0xF0;            // AN pinleri analog giri� olarak yap�land�r�ld�
  CMCON  |= 7;               // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISD = 0x00;                  // PORTD ��k�� yap�ld�
  PORTD = 0x00;                  // PORTD temizlendi
  
  TRISC = 0x00;                  // PORTC ��k�� yap�ld�
  PORTC = 0x00;                  // PORTC temizlendi

  TRISA  = 0xFF;                 // PORTA is input

  while(1)                       // Sonsuz d�ng�
  {
     adc_sinyal = ADC_Read(2);   // 10-bit sonu� elde ediliyor
     PORTD = adc_sinyal;         // LSB 8-bit PORTB'de
     PORTC = adc_sinyal >> 8;    // MSB 2-bit RC1 ve RC0 pinlerinde
  }                              // g�steriliyor

}