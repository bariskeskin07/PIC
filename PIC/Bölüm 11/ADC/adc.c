unsigned int adc_sinyal;

void main() {

  ADCON0 = 0x09;             // A/D donaným birimi aktif edildi
  ADCON1 &= 0xF0;            // AN pinleri analog giriþ olarak yapýlandýrýldý
  CMCON  |= 7;               // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISD = 0x00;                  // PORTD çýkýþ yapýldý
  PORTD = 0x00;                  // PORTD temizlendi
  
  TRISC = 0x00;                  // PORTC çýkýþ yapýldý
  PORTC = 0x00;                  // PORTC temizlendi

  TRISA  = 0xFF;                 // PORTA is input

  while(1)                       // Sonsuz döngü
  {
     adc_sinyal = ADC_Read(2);   // 10-bit sonuç elde ediliyor
     PORTD = adc_sinyal;         // LSB 8-bit PORTB'de
     PORTC = adc_sinyal >> 8;    // MSB 2-bit RC1 ve RC0 pinlerinde
  }                              // gösteriliyor

}