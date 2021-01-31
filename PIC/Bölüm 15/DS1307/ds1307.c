// Software I2C baðlantýlarý
sbit Soft_I2C_Scl           at RB7_bit;
sbit Soft_I2C_Sda           at RB6_bit;
sbit Soft_I2C_Scl_Direction at TRISB7_bit;
sbit Soft_I2C_Sda_Direction at TRISB6_bit;
// End Software I2C baðlantýlarý


// LCD module baðlantýlarý
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module baðlantýlarý

char seconds, minutes, hours, week_day, day, month, year;

//--------------------- RTC (DS1307) 'den zaman ve tarih okunuyor
void Read_Time() {

  Soft_I2C_Start();               // Start sinyali oluþturuluyor
  Soft_I2C_Write(0xD0);           // DS1307'nin adresi gönderiliyor (DS1307 datasheets)
  Soft_I2C_Write(0);              // Adres 0'dan baþlanýyor
  Soft_I2C_Start();               // Start sinyali tekrarlanýyor
  Soft_I2C_Write(0xD1);           // DS1307'nin adresi gönderiliyor (R/W=1)

  seconds = Soft_I2C_Read(1);     // saniye bilgisi okundu
  minutes = Soft_I2C_Read(1);     // dakika bilgisi okundu
  hours = Soft_I2C_Read(1);       // saat bilgisi okundu
  week_day = Soft_I2C_Read(1);    // haftanýn günü bilgisi okundu
  day = Soft_I2C_Read(1);         // ayýn günü bilgisi okundu
  month = Soft_I2C_Read(1);       // ay bilgisi okundu
  year = Soft_I2C_Read(0);        // yýl bilgisi okundu
  Soft_I2C_Stop();                // stop sinyali gönderildi

}

//-------------------- Tarih ve saat formatlarý LCD'ye göre düzenleniyor
void Transform_Time() {
  seconds  =  ((seconds & 0xF0) >> 4)*10 + (seconds & 0x0F);  // saniye dönüþtürüldü
  minutes  =  ((minutes & 0xF0) >> 4)*10 + (minutes & 0x0F);  // dakika dönüþtürüldü
  hours    =  ((hours & 0xF0)  >> 4)*10  + (hours & 0x0F);    // saat dönüþtürüldü
  year     =  ((year & 0xF0) >> 4)*10 + (year & 0x0F);        // yýl dönüþtürüldü
  day      =  ((day & 0x30) >> 4)*10    + (day & 0x0F);       // gün dönüþtürüldü
  month    =  ((month & 0x10)  >> 4)*10 + (month & 0x0F);     // ay dönüþtürüldü
}

//-------------------- Tarih ve saat LCD display'e gönderiliyor
void Display_Time() {

   Lcd_Chr(1, 6, (day / 10)   + 48);    // günün onlar basamaðý gönderiliyor
   Lcd_Chr(1, 7, (day % 10)   + 48);    // günün birler basamaðý gönderiliyor
   Lcd_Chr(1, 9, (month / 10) + 48);    // ayýn onlar basamaðý gönderiliyor
   Lcd_Chr(1,10, (month % 10) + 48);    // ayýn birler basamaðý gönderiliyor
   Lcd_Chr(1,14, (year / 10)  + 48);    // yýlýn onlar basamaðý gönderiliyor
   Lcd_Chr(1,15, (year % 10)  + 48);    // yýlýn birler basamaðý gönderiliyor

   Lcd_Chr(2, 6, (hours / 10)   + 48);  // saatin onlar basamaðý gönderiliyor
   Lcd_Chr(2, 7, (hours % 10)   + 48);  // saatin birler basamaðý gönderiliyor
   Lcd_Chr(2, 9, (minutes / 10) + 48);  // dakikanýn onlar basamaðý gönderiliyor
   Lcd_Chr(2,10, (minutes % 10) + 48);  // dakikanýn birler basamaðý gönderiliyor
   Lcd_Chr(2,12, (seconds / 10) + 48);  // saniyenin onlar basamaðý gönderiliyor
   Lcd_Chr(2,13, (seconds % 10) + 48);  // saniyenin birler basamaðý gönderiliyor
}

//------------------ PIC için baþlangýç yapýlandýrma ayarlarý
void Init_Main() {
  TRISB = 0;                 // PORTB'yi çýkýþa yönlendir
  PORTB = 0xFF;              // PORTB'ye 0xFF yükle
  TRISB = 0xff;              // PORTB'yi giriþe yönlendir

  Soft_I2C_Init();           // yazýlýmsal I2C iletiþimi ayarla
  Lcd_Init();                // LCD displayi yapýlandýr
  Lcd_Cmd(_LCD_CLEAR);       // LCD display ekranýný temizle
  Lcd_Cmd(_LCD_CURSOR_OFF);  // LCD display ekranýndan imleci kaldýr

  Lcd_Out(1,1,"Date:");      // LCD display'de görüntüle
  Lcd_Chr(1,8,'.');
  Lcd_Chr(1,11,'.');
  Lcd_Out(2,1,"Time:");
  Lcd_Chr(2,8,':');
  Lcd_Chr(2,11,':');
  Lcd_Out(1,12,"20");
}

void main() {
  Delay_ms(500);             // 0.5 sn bekle
  Init_Main();               // Yapýlandýrma alt programýný çaðýr

  while (1) {                // sonsuz döngü
    Read_Time();             // RTC(DS1307)'den tarih ve zamaný oku
    Transform_Time();        // formatýný ayarla
    Display_Time();          // LCD display'de görüntüle
  }
}
