void init()
{
  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;            // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISC.RC2 = 0;          // RC2/P1A pini çýkýþ yapýldý
  PORTC.RC2 = 0;          // RC2/P1A pini sýfýrlandý

  TRISD.RD5 = 0;          // RD5/P1B pini çýkýþ yapýldý
  PORTD.RD5 = 0;          // RD5/P1B pini sýfýrlandý

  TRISD.RD6 = 0;          // RD6/P1C pini çýkýþ yapýldý
  PORTD.RD6 = 0;          // RD6/P1C pini sýfýrlandý

  TRISD.RD7 = 0;          // RD7/P1D pini çýkýþ yapýldý
  PORTD.RD7 = 0;          // RD7/P1D pini sýfýrlandý

  CCP1CON = 0xCC;         // ECCP birimi PWM Full-Bridge moduna yapýlandýrýldý
  CCPR1L = 0x0F;          // duty cycle oraný belirlendi
  CCPR1H = 0x00;
  PR2 = 99;               // PWM peryodu belirleniyor (10000 Hz)
  T2CON = 0x04;           // Timer2 1:1 prescaler deðerine yapýlandýrýldý
  ECCP1AS.ECCPAS2 = 0;    //
  ECCP1AS.ECCPAS1 = 0;    //  ECCP1AS Kaydedicisi ECCPAS2:ECCPAS0 bitleri 0
  ECCP1AS.ECCPAS0 = 0;    //  yapýlarak, otomatik kapanma pasif edildi.
}

void main() {

   init();                // init() isimli altprogram çaðrýldý
   while(1);              // Sonsuz döngü.

}