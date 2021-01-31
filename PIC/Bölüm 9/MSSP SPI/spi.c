sbit ST_CP at RB7_bit;                   // ST_CP = RB7 olarak tan�mland�
sbit ST_CP_Direction at TRISB7_bit;

void init()               // init alt program�
{
  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;            // Comparators (kar��la�t�r�c�lar) pasif edildi
  
  ST_CP_Direction = 0;    // RB7 pini ��k�� yap�ld�

  SPI1_Init();            // SPI donan�m birimi yap�land�r�ld�
  
  ST_CP = 0;              // RB7 pini lojik 0 yap�ld�
  SPI1_Write(0x81);       // SPI donan�m birimine 0x81 yaz�ld�
  ST_CP = 1;              // RB7 pini lojik 1 yap�ld�
}

void main() {

   init();                // init() isimli altprogram �a�r�ld�
   while(1);              // Sonsuz d�ng�
}