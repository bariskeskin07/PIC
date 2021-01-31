void init()
{
  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;            // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISC.RC2 = 0;          // RC2/P1A pini ��k�� yap�ld�
  PORTC.RC2 = 0;          // RC2/P1A pini s�f�rland�

  TRISD.RD5 = 0;          // RD5/P1B pini ��k�� yap�ld�
  PORTD.RD5 = 0;          // RD5/P1B pini s�f�rland�

  TRISD.RD6 = 0;          // RD6/P1C pini ��k�� yap�ld�
  PORTD.RD6 = 0;          // RD6/P1C pini s�f�rland�

  TRISD.RD7 = 0;          // RD7/P1D pini ��k�� yap�ld�
  PORTD.RD7 = 0;          // RD7/P1D pini s�f�rland�

  CCP1CON = 0xCC;         // ECCP birimi PWM Full-Bridge moduna yap�land�r�ld�
  CCPR1L = 0x0F;          // duty cycle oran� belirlendi
  CCPR1H = 0x00;
  PR2 = 99;               // PWM peryodu belirleniyor (10000 Hz)
  T2CON = 0x04;           // Timer2 1:1 prescaler de�erine yap�land�r�ld�
  ECCP1AS.ECCPAS2 = 0;    //
  ECCP1AS.ECCPAS1 = 0;    //  ECCP1AS Kaydedicisi ECCPAS2:ECCPAS0 bitleri 0
  ECCP1AS.ECCPAS0 = 0;    //  yap�larak, otomatik kapanma pasif edildi.
}

void main() {

   init();                // init() isimli altprogram �a�r�ld�
   while(1);              // Sonsuz d�ng�.

}