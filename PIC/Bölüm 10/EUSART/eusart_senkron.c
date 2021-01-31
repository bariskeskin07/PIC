#define   oku_butonu   portc.rc0

char uart_rd;                   // EUSART biriminden al�nacak olan veri i�in
                                // tan�mlanan de�i�ken
// LCD display ba�lant�lar�
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
// LCD display ba�lant� sonu

void main(){

   ADCON1 |= 0x0F;                      // AN pinleri dijital I/O yap�land�r�ld�
   CMCON  |= 7;                         // Comparators (kar��la�t�r�c�lar) pasif edildi
   
   trisc.rc5 = 1;
   portc.rc5 = 0;
   
   trisc.rc0 = 0;
   oku_butonu = 0;

   Lcd_Init();                          // LCD display yap�land�r�ld�
   Lcd_Cmd(_LCD_CURSOR_OFF);            // LCD ekran�ndan imle� kald�r�ld�
   Lcd_Cmd(_LCD_CLEAR);                 // LCD ekran� silindi
   Lcd_Out(1, 3, "Sivas EML");          // 1. sat�r, 3. s�tun'a text yazd�r�ld�
   Lcd_Out(2, 1, "Elektronik Blm.");    // 2. sat�r, 1. s�tun'a text yazd�r�ld�

   UART1_Init(9600);                    // EUSART donan�m� yap�land�r�ld�
   Delay_ms(100);                        // Baud h�z� 57600 belirlendi

   for( ; ; )
   {
      if (UART1_Data_Ready()) {     // �ayet EUSART'dan veri geldi ise,
      uart_rd = UART1_Read();       // Al�nan veriyi oku, uart_rd'ye al,
      UART1_Write(uart_rd);         // ve EUSART'a veriyi yaz
      Lcd_Chr_Cp(uart_rd);          // Al�nan veriyi LCD ekran�na g�nder
      if (uart_rd == 27) Lcd_Cmd(_LCD_CLEAR);        // ESC display ekran�n� sil
      if (uart_rd == 13) Lcd_Cmd(_LCD_SECOND_ROW);   // ENTER display 2. sat�r
    }
   }

}