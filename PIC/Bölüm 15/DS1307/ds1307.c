// Software I2C ba�lant�lar�
sbit Soft_I2C_Scl           at RB7_bit;
sbit Soft_I2C_Sda           at RB6_bit;
sbit Soft_I2C_Scl_Direction at TRISB7_bit;
sbit Soft_I2C_Sda_Direction at TRISB6_bit;
// End Software I2C ba�lant�lar�


// LCD module ba�lant�lar�
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
// End LCD module ba�lant�lar�

char seconds, minutes, hours, week_day, day, month, year;

//--------------------- RTC (DS1307) 'den zaman ve tarih okunuyor
void Read_Time() {

  Soft_I2C_Start();               // Start sinyali olu�turuluyor
  Soft_I2C_Write(0xD0);           // DS1307'nin adresi g�nderiliyor (DS1307 datasheets)
  Soft_I2C_Write(0);              // Adres 0'dan ba�lan�yor
  Soft_I2C_Start();               // Start sinyali tekrarlan�yor
  Soft_I2C_Write(0xD1);           // DS1307'nin adresi g�nderiliyor (R/W=1)

  seconds = Soft_I2C_Read(1);     // saniye bilgisi okundu
  minutes = Soft_I2C_Read(1);     // dakika bilgisi okundu
  hours = Soft_I2C_Read(1);       // saat bilgisi okundu
  week_day = Soft_I2C_Read(1);    // haftan�n g�n� bilgisi okundu
  day = Soft_I2C_Read(1);         // ay�n g�n� bilgisi okundu
  month = Soft_I2C_Read(1);       // ay bilgisi okundu
  year = Soft_I2C_Read(0);        // y�l bilgisi okundu
  Soft_I2C_Stop();                // stop sinyali g�nderildi

}

//-------------------- Tarih ve saat formatlar� LCD'ye g�re d�zenleniyor
void Transform_Time() {
  seconds  =  ((seconds & 0xF0) >> 4)*10 + (seconds & 0x0F);  // saniye d�n��t�r�ld�
  minutes  =  ((minutes & 0xF0) >> 4)*10 + (minutes & 0x0F);  // dakika d�n��t�r�ld�
  hours    =  ((hours & 0xF0)  >> 4)*10  + (hours & 0x0F);    // saat d�n��t�r�ld�
  year     =  ((year & 0xF0) >> 4)*10 + (year & 0x0F);        // y�l d�n��t�r�ld�
  day      =  ((day & 0x30) >> 4)*10    + (day & 0x0F);       // g�n d�n��t�r�ld�
  month    =  ((month & 0x10)  >> 4)*10 + (month & 0x0F);     // ay d�n��t�r�ld�
}

//-------------------- Tarih ve saat LCD display'e g�nderiliyor
void Display_Time() {

   Lcd_Chr(1, 6, (day / 10)   + 48);    // g�n�n onlar basama�� g�nderiliyor
   Lcd_Chr(1, 7, (day % 10)   + 48);    // g�n�n birler basama�� g�nderiliyor
   Lcd_Chr(1, 9, (month / 10) + 48);    // ay�n onlar basama�� g�nderiliyor
   Lcd_Chr(1,10, (month % 10) + 48);    // ay�n birler basama�� g�nderiliyor
   Lcd_Chr(1,14, (year / 10)  + 48);    // y�l�n onlar basama�� g�nderiliyor
   Lcd_Chr(1,15, (year % 10)  + 48);    // y�l�n birler basama�� g�nderiliyor

   Lcd_Chr(2, 6, (hours / 10)   + 48);  // saatin onlar basama�� g�nderiliyor
   Lcd_Chr(2, 7, (hours % 10)   + 48);  // saatin birler basama�� g�nderiliyor
   Lcd_Chr(2, 9, (minutes / 10) + 48);  // dakikan�n onlar basama�� g�nderiliyor
   Lcd_Chr(2,10, (minutes % 10) + 48);  // dakikan�n birler basama�� g�nderiliyor
   Lcd_Chr(2,12, (seconds / 10) + 48);  // saniyenin onlar basama�� g�nderiliyor
   Lcd_Chr(2,13, (seconds % 10) + 48);  // saniyenin birler basama�� g�nderiliyor
}

//------------------ PIC i�in ba�lang�� yap�land�rma ayarlar�
void Init_Main() {
  TRISB = 0;                 // PORTB'yi ��k��a y�nlendir
  PORTB = 0xFF;              // PORTB'ye 0xFF y�kle
  TRISB = 0xff;              // PORTB'yi giri�e y�nlendir

  Soft_I2C_Init();           // yaz�l�msal I2C ileti�imi ayarla
  Lcd_Init();                // LCD displayi yap�land�r
  Lcd_Cmd(_LCD_CLEAR);       // LCD display ekran�n� temizle
  Lcd_Cmd(_LCD_CURSOR_OFF);  // LCD display ekran�ndan imleci kald�r

  Lcd_Out(1,1,"Date:");      // LCD display'de g�r�nt�le
  Lcd_Chr(1,8,'.');
  Lcd_Chr(1,11,'.');
  Lcd_Out(2,1,"Time:");
  Lcd_Chr(2,8,':');
  Lcd_Chr(2,11,':');
  Lcd_Out(1,12,"20");
}

void main() {
  Delay_ms(500);             // 0.5 sn bekle
  Init_Main();               // Yap�land�rma alt program�n� �a��r

  while (1) {                // sonsuz d�ng�
    Read_Time();             // RTC(DS1307)'den tarih ve zaman� oku
    Transform_Time();        // format�n� ayarla
    Display_Time();          // LCD display'de g�r�nt�le
  }
}
