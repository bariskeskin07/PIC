void init()
{
  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;            // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISC.RC2 = 0;          // RC2/P1A pini çýkýþ yapýldý
  PORTC.RC2 = 0;          // RC2/P1A pini sýfýrlandý

  TRISD.RD5 = 0;          // RD5/P1B pini çýkýþ yapýldý
  PORTD.RD5 = 0;          // RD5/P1B pini sýfýrlandý

  CCP1CON = 0x8C;         // ECCP birimi PWM Half-Bridge moduna yapýlandýrýldý
  CCPR1L = 0x0F;          // duty cycle oraný belirlendi
  CCPR1H = 0x00;
  PR2 = 99;               // PWM peryodu belirleniyor (10000 Hz)
  T2CON = 0x04;           // Timer2 1:1 prescaler deðerine yapýlandýrýldý
}

void main() {

   init();                // init() isimli altprogram çaðrýldý
   while(1);              // Sonsuz döngü.

}