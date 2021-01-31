void init()
{
  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;            // Comparators (karþýlaþtýrýcýlar) pasif edildi
  
  TRISC.RC2 = 0;          // RC2/P1A pini çýkýþ yapýldý
  PORTC.RC2 = 0;          // RC2/P1A pini sýfýrlandý
  
//  TRISD.RD5 = 0;
//  PORTD.RD5 = 0;
  
  CCP1CON = 0x0C; //0x8C; // ECCP birimi tek çýkýþ PWM moduna yapýlandýrýldý
  CCPR1L = 0x0F;          // duty cycle oraný belirlendi
  CCPR1H = 0x00;  
  PR2 = 99;               // PWM peryodu belirleniyor (10000 Hz)
  T2CON = 0x04;           // Timer2 1:1 prescaler deðerine yapýlandýrýldý
}

void main() {

   init();                // init() isimli altprogram çaðrýldý
   while(1);              // Sonsuz döngü.

}