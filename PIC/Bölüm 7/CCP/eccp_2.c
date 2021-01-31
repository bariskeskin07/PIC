void init()
{
  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;            // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISC.RC2 = 0;          // RC2/P1A pini ��k�� yap�ld�
  PORTC.RC2 = 0;          // RC2/P1A pini s�f�rland�

  TRISD.RD5 = 0;          // RD5/P1B pini ��k�� yap�ld�
  PORTD.RD5 = 0;          // RD5/P1B pini s�f�rland�

  CCP1CON = 0x8C;         // ECCP birimi PWM Half-Bridge moduna yap�land�r�ld�
  CCPR1L = 0x0F;          // duty cycle oran� belirlendi
  CCPR1H = 0x00;
  PR2 = 99;               // PWM peryodu belirleniyor (10000 Hz)
  T2CON = 0x04;           // Timer2 1:1 prescaler de�erine yap�land�r�ld�
}

void main() {

   init();                // init() isimli altprogram �a�r�ld�
   while(1);              // Sonsuz d�ng�.

}