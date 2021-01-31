#include "built_in.h"

unsigned tmr3_ondeger = 3036;
unsigned cnt;

void interrupt() {
  if (PIR2.TMR3IF) {          // TMR3IF biti kontrol ediliyor (kesme oluþtu mu?)
    portb++;                  // portb 'nin içeriðini 1 artýr
    TMR3H = hi(tmr3_ondeger); // TMR3H ve TMR3L kaydedici çiftine ön deðer
    TMR3L = lo(tmr3_ondeger); // yüklendi (3036 = 0x0BDC)
    TMR3IF_bit = 0;           // TMR3IF sýfýrlandý
  }
}

void main() {

  ADCON1 |= 0x0F;      // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;         // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISB = 0;           // PORTB çýkýþ yapýldý
  PORTB = 0xFF;        // PORTB ayarlandý

  cnt = 0;
  TMR3H = hi(tmr3_ondeger);   // TMR3H = 0x0B
  TMR3L = lo(tmr3_ondeger);   // TMR3L = 0xDC
  
  T3CON  = 0xB5;              // TMR3 16bit zamanlayýcý, prescaler 11 = 8
  INTCON.GIE = 1;             // GIE biti set edildi
  PEIE_bit = 1;               // PEIE biti set edildi
  PIE2.TMR3IE = 1;            // TMR3 kesmesi aktif edildi

  while(1)
  {
                              // ana program
  }

}