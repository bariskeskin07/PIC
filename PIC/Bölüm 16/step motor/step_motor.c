#define         step_motor      portd
#define         tam_ileri       portb.rb0
#define         tam_geri        portb.rb1
#define         yarim_ileri     portb.rb2
#define         yarim_geri      portb.rb3

char pos = 0x07;
char yarim_adim[8] = {0x03,0x02,0x06,0x04,0x0c,0x08,0x09,0x01};
char tam_adim[8] = {0x06,0x0c,0x09,0x03};

void ileri(char mod)     // step motor ileri hareket eder
{
   if (mod)       // mod = 1 tam ad�m ileri
   {
      if (pos < 3) pos++; else pos = 0;
      step_motor = tam_adim[pos];   // step motor ad�m pozisyonu
   }
   else           // mod = 0 yar�m ad�m ileri
   {
      if (pos < 7) pos++; else pos = 0;
      step_motor = yarim_adim[pos]; // step motor ad�m pozisyonu
   }
   delay_ms(500);
}

void geri(char mod)      // step motor geri hareket eder
{
   if (mod)       // mod = 1 tam ad�m geri
   {
      if (pos > 0) pos--; else pos = 3;
      step_motor = tam_adim[pos];   // step motor ad�m pozisyonu
   }
   else           // mod = 0 tam ad�m geri
   {
      if (pos > 0) pos--; else pos = 7;
      step_motor = yarim_adim[pos];  // step motor ad�m pozisyonu
   }
   delay_ms(500);
}

void init()
{
   ADCON1 |= 0x0F;             // AN pinleri dijital I/O yap�land�r�ld�
   CMCON  |= 7;                // Comparators (kar��la�t�r�c�lar) pasif edildi
   trisd = 0x00;
   portd = 0x00;

}

void main() {
   init();
   
   while(1)
   {
      if (tam_ileri) ileri(1);
      if (yarim_ileri) ileri(0);
      if (tam_geri) geri(1);
      if (yarim_geri) geri(0);
   }
}