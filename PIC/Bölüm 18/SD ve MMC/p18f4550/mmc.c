// MMC modüle baðlantýlarý
sbit Mmc_Chip_Select           at LATC0_bit;  // for writing to output pin always use latch (PIC18 family)
sbit Mmc_Chip_Select_Direction at TRISC0_bit;
// eof MMC modüle baðlantýlarý

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

// Program içerisinde kullanýlacak olan global deðiþkenler tanýmlanýyor
char mesaj[35] = "    . sektore yazma islemi tamam!";
char Buffer[512] = {"Bu program HIKMET SAHIN tarafindan 16.01.2012 tarihinde yazilmistir..."};
char dataBuffer[512];
unsigned int sector_no;
                             
// UART1 modülüne text yazýmý ve yeni satýr (enter + line feed)
void UART1_Write_Line(char *uart_text) {
  UART1_Write_Text(uart_text);
  UART1_Write(13);
  UART1_Write(10);
}

// MMC sektör numaralarý basamaklarýna ayrýlýyor ve dizi deðiþkene aktarýlýyor
void sektoru_basamakla()
{
   mesaj[0] = sector_no/1000 + 48;
   mesaj[1] = (sector_no/100)%10 + 48;
   mesaj[2] = (sector_no/10)%10 + 48;
   mesaj[3] = sector_no%10 + 48;
}

void main() {
  ADCON1 |= 0x0F;                  // AN pinleri I/O olarak yapýlandýrýldý
  CMCON  |= 7;                     // Komparatörler kapatýldý

  UART1_Init(19200);               // UART1 modülü 19200 baud'a yapýlandýrýldý
  Delay_ms(10);
  
  Lcd_Init();                      // LCD display yapýlandýrýldý
  Lcd_Cmd(_LCD_CURSOR_OFF);        // Ýmleç ekrandan kaldýrýldý
  Lcd_Cmd(_LCD_CLEAR);             // Ekran silindi
  Lcd_Out(1, 1, "SD/MMC Kart");    // LCD ekran 1.satýrýna text gönderildi
  Lcd_Out(2, 1, "Uygulamasi");     // LCD ekran 2.satýrýna text gönderildi

  UART1_Write_Line("PIC-Hazir!");  // PIC hazýr raporu
  delay_ms(500);

  // SPI1 modülü yapýlandýrýlýyor
  SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV64, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);

  // MMC/SD kart yapýlandýrýlýyor ve FAT16 biçiminde formatlanýyor
  if (Mmc_Fat_Init() == 1) {
    if (Mmc_Fat_QuickFormat("card.mmc")) UART1_Write_Line("Quick Format Tamam!");
    UART1_Write_Line("");          // Boþ satýr
    for(sector_no = 0; sector_no < 20; sector_no++)
    {
       sektoru_basamakla();
       Lcd_Out(2, 1, "SEKTOR YAZILIYOR");
       // Belirlenen sektör numarasýna Buffer'daki veriler yazdýrýlýyor
       if (0 == Mmc_Write_Sector(sector_no, Buffer)) UART1_Write_Line(mesaj); else break;
    }
  } else UART1_Write_Line("MMC karti takiniz!");
  
  delay_ms(500);
  
  // Belirlenen sektör numarasýndaki veriler dataBuffer deðiþkenine alýnýyor
  if (Mmc_Fat_Init() == 1) {
     if (!Mmc_Read_Sector(0, dataBuffer)) {
        // dataBuffer deðiþkeni UART1 modülüne yazdýrýlýyor
        UART1_Write_Line("OKUNAN VERi :");
        UART1_Write_Line(dataBuffer);
        Lcd_Out(2, 1, "SEKTOR OKUNDU!..");
     }
  }
  else {
     UART1_Write_Line("MMC karti takiniz!");
     Lcd_Out(2, 1, "TAKINIZ!..");
  }
}