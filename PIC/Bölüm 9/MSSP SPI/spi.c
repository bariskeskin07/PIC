sbit ST_CP at RB7_bit;                   // ST_CP = RB7 olarak tanýmlandý
sbit ST_CP_Direction at TRISB7_bit;

void init()               // init alt programý
{
  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;            // Comparators (karþýlaþtýrýcýlar) pasif edildi
  
  ST_CP_Direction = 0;    // RB7 pini çýkýþ yapýldý

  SPI1_Init();            // SPI donaným birimi yapýlandýrýldý
  
  ST_CP = 0;              // RB7 pini lojik 0 yapýldý
  SPI1_Write(0x81);       // SPI donaným birimine 0x81 yazýldý
  ST_CP = 1;              // RB7 pini lojik 1 yapýldý
}

void main() {

   init();                // init() isimli altprogram çaðrýldý
   while(1);              // Sonsuz döngü
}