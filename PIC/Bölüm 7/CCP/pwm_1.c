unsigned short aktif_duty1, aktif_duty2;

void init()
{
  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;            // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISB = 0xFF;           // PORTB giriþ yapýldý
  PORTB = 0x00;           // PORTB temizlendi

  PWM1_Init(500);         // PWM1 modülü 500 Hz'e ayarlandý
  PWM2_Init(500);         // PWM2 modülü 500 Hz'e ayarlandý
}

void main() {

   init();                             // init() isimli altprogram çaðrýldý
   aktif_duty1 = 16;                   // aktif_duty1 deðiþkenine 16 yüklendi
   aktif_duty2 = 100;                  // aktif_duty2 deðiþkenine 100 yüklendi

   PWM1_Start();                       // PWM1 baþlatýldý
   PWM2_Start();                       // PWM2 baþlatýldý
   PWM1_Set_Duty(aktif_duty1);         // PWM1 için duty_cycle set edildi
   PWM2_Set_Duty(aktif_duty2);         // PWM2 için duty_cycle set edildi

   while(1)                            // Sonsuz döngü.
   {
      if (RB6_bit) {                   // RB6 butonuna basýldý mý?
         delay_ms(40);                 // 40 ms bekle
         aktif_duty1++;                // aktif_duty1 deðerini 1 artýr
         PWM1_Set_Duty(aktif_duty1);   // PWM1 için yeni duty_cycle set edildi
      }
      
      if (RB7_bit) {                   // RB7 butonuna basýldý mý?
         delay_ms(40);                 // 40 ms bekle
         aktif_duty1--;                // aktif_duty1 deðerini 1 azalt
         PWM1_Set_Duty(aktif_duty1);   // PWM1 için yeni duty_cycle set edildi
      }
   }

}