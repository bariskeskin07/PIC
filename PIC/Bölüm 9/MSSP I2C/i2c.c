void main() {

  ADCON1 |= 0x0F;            // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;               // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISD = 0x00;              // PORTD ��k�� yap�ld�
  PORTD = 0x00;              // PORTD temizlendi

  I2C1_Init(100000);         // I2C ileti�im yap�land�r�ld�
  I2C1_Start();              // I2C start sinyal
  I2C1_Wr(0xA2);             // I2C ile 1 byte g�nderildi (cihaz adres + W)
  I2C1_Wr(2);                // 1 byte g�nderildi (EEPROM'a yaz�lacak adres)
  I2C1_Wr(0xAA);             // veri g�nderildi (data yaz�ld�)
  I2C1_Stop();
  
  Delay_100ms();             // 100 ms bekle

  I2C1_Start();              // I2C start sinyal
  I2C1_Wr(0xA2);             // I2C ile 1 byte g�nderildi (cihaz adres + W)
  I2C1_Wr(2);                // 1 byte g�nderildi (data adres)
  I2C1_Repeated_Start();     // I2C start sinyali tekrarland�
  I2C1_Wr(0xA3);             // 1 byte g�nderildi(cihaz adres + R)
  PORTD = I2C1_Rd(0u);       // veri okundu (NO acknowledge)
  I2C1_Stop();               // I2C stop sinyal

  while(1);                  // Sonsuz d�ng�

}