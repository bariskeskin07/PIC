#define   oku_butonu   portc.rc0

char uart_rd;                   // EUSART biriminden alýnacak olan veri için
                                // tanýmlanan deðiþken
// LCD display baðlantýlarý
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;
// LCD display baðlantý sonu

void main(){

   ADCON1 |= 0x0F;                      // AN pinleri dijital I/O yapýlandýrýldý
   CMCON  |= 7;                         // Comparators (karþýlaþtýrýcýlar) pasif edildi
   
   trisc.rc5 = 1;
   portc.rc5 = 0;
   
   trisc.rc0 = 0;
   oku_butonu = 0;

   Lcd_Init();                          // LCD display yapýlandýrýldý
   Lcd_Cmd(_LCD_CURSOR_OFF);            // LCD ekranýndan imleç kaldýrýldý
   Lcd_Cmd(_LCD_CLEAR);                 // LCD ekraný silindi
   Lcd_Out(1, 3, "Sivas EML");          // 1. satýr, 3. sütun'a text yazdýrýldý
   Lcd_Out(2, 1, "Elektronik Blm.");    // 2. satýr, 1. sütun'a text yazdýrýldý

   UART1_Init(9600);                    // EUSART donanýmý yapýlandýrýldý
   Delay_ms(100);                        // Baud hýzý 57600 belirlendi

   for( ; ; )
   {
      if (UART1_Data_Ready()) {     // Þayet EUSART'dan veri geldi ise,
      uart_rd = UART1_Read();       // Alýnan veriyi oku, uart_rd'ye al,
      UART1_Write(uart_rd);         // ve EUSART'a veriyi yaz
      Lcd_Chr_Cp(uart_rd);          // Alýnan veriyi LCD ekranýna gönder
      if (uart_rd == 27) Lcd_Cmd(_LCD_CLEAR);        // ESC display ekranýný sil
      if (uart_rd == 13) Lcd_Cmd(_LCD_SECOND_ROW);   // ENTER display 2. satýr
    }
   }

}