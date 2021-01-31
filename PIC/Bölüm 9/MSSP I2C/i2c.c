void main() {

  ADCON1 |= 0x0F;            // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;               // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISD = 0x00;              // PORTD çýkýþ yapýldý
  PORTD = 0x00;              // PORTD temizlendi

  I2C1_Init(100000);         // I2C iletiþim yapýlandýrýldý
  I2C1_Start();              // I2C start sinyal
  I2C1_Wr(0xA2);             // I2C ile 1 byte gönderildi (cihaz adres + W)
  I2C1_Wr(2);                // 1 byte gönderildi (EEPROM'a yazýlacak adres)
  I2C1_Wr(0xAA);             // veri gönderildi (data yazýldý)
  I2C1_Stop();
  
  Delay_100ms();             // 100 ms bekle

  I2C1_Start();              // I2C start sinyal
  I2C1_Wr(0xA2);             // I2C ile 1 byte gönderildi (cihaz adres + W)
  I2C1_Wr(2);                // 1 byte gönderildi (data adres)
  I2C1_Repeated_Start();     // I2C start sinyali tekrarlandý
  I2C1_Wr(0xA3);             // 1 byte gönderildi(cihaz adres + R)
  PORTD = I2C1_Rd(0u);       // veri okundu (NO acknowledge)
  I2C1_Stop();               // I2C stop sinyal

  while(1);                  // Sonsuz döngü

}