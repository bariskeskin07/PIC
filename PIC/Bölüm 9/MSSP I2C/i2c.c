void main() {

  ADCON1 |= 0x0F;            // AN pinleri dijital I/O yapılandırıldı
  CMCON  |= 7;               // Comparators (karşılaştırıcılar) pasif edildi

  TRISD = 0x00;              // PORTD çıkış yapıldı
  PORTD = 0x00;              // PORTD temizlendi

  I2C1_Init(100000);         // I2C iletişim yapılandırıldı
  I2C1_Start();              // I2C start sinyal
  I2C1_Wr(0xA2);             // I2C ile 1 byte gönderildi (cihaz adres + W)
  I2C1_Wr(2);                // 1 byte gönderildi (EEPROM'a yazılacak adres)
  I2C1_Wr(0xAA);             // veri gönderildi (data yazıldı)
  I2C1_Stop();
  
  Delay_100ms();             // 100 ms bekle

  I2C1_Start();              // I2C start sinyal
  I2C1_Wr(0xA2);             // I2C ile 1 byte gönderildi (cihaz adres + W)
  I2C1_Wr(2);                // 1 byte gönderildi (data adres)
  I2C1_Repeated_Start();     // I2C start sinyali tekrarlandı
  I2C1_Wr(0xA3);             // 1 byte gönderildi(cihaz adres + R)
  PORTD = I2C1_Rd(0u);       // veri okundu (NO acknowledge)
  I2C1_Stop();               // I2C stop sinyal

  while(1);                  // Sonsuz döngü

}