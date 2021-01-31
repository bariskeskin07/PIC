#define         sil     portb.rb5
#define         yaz     portb.rb6
#define         sola    portb.rb7

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

void main(){

   ADCON1 |= 0x0F;
   CMCON  |= 7;

   Lcd_Init();
   Lcd_Cmd(_LCD_CURSOR_OFF);
   Lcd_Cmd(_LCD_CLEAR);
   Lcd_Out(1, 3, "Sivas EML");
   Lcd_Out(2, 1, "Elektronik Blm.");
   
   for( ; ; )
   {
      if (sil) LCD_Cmd(_LCD_CLEAR);
      if (yaz){
         Lcd_Out(1, 2, "MikroC harika");
         Lcd_Out(2, 2, "Bir Program!");
      }
      if (sola){
         LCD_Cmd(_LCD_SHIFT_RIGHT);
         while(sola);
      }
   }

}