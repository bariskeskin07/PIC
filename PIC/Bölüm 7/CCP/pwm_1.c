unsigned short aktif_duty1, aktif_duty2;

void init()
{
  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;            // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISB = 0xFF;           // PORTB giri� yap�ld�
  PORTB = 0x00;           // PORTB temizlendi

  PWM1_Init(500);         // PWM1 mod�l� 500 Hz'e ayarland�
  PWM2_Init(500);         // PWM2 mod�l� 500 Hz'e ayarland�
}

void main() {

   init();                             // init() isimli altprogram �a�r�ld�
   aktif_duty1 = 16;                   // aktif_duty1 de�i�kenine 16 y�klendi
   aktif_duty2 = 100;                  // aktif_duty2 de�i�kenine 100 y�klendi

   PWM1_Start();                       // PWM1 ba�lat�ld�
   PWM2_Start();                       // PWM2 ba�lat�ld�
   PWM1_Set_Duty(aktif_duty1);         // PWM1 i�in duty_cycle set edildi
   PWM2_Set_Duty(aktif_duty2);         // PWM2 i�in duty_cycle set edildi

   while(1)                            // Sonsuz d�ng�.
   {
      if (RB6_bit) {                   // RB6 butonuna bas�ld� m�?
         delay_ms(40);                 // 40 ms bekle
         aktif_duty1++;                // aktif_duty1 de�erini 1 art�r
         PWM1_Set_Duty(aktif_duty1);   // PWM1 i�in yeni duty_cycle set edildi
      }
      
      if (RB7_bit) {                   // RB7 butonuna bas�ld� m�?
         delay_ms(40);                 // 40 ms bekle
         aktif_duty1--;                // aktif_duty1 de�erini 1 azalt
         PWM1_Set_Duty(aktif_duty1);   // PWM1 i�in yeni duty_cycle set edildi
      }
   }

}