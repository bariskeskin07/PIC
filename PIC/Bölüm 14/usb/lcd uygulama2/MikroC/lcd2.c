#include "USBdsc.c"

// LCD module connections
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
// End LCD module connections

unsigned char readbuff[64] absolute 0x500;
unsigned char writebuff[64] absolute 0x540;

char text_kod;
char text_uzunlugu;
unsigned short i;

void interrupt(){
   USB_Interrupt_Proc();
}

void main(){

   ADCON0 = 0;
   ADCON1 |= 0x0F;
   ADCON2 = 0;
   CMCON  |= 7;

   Lcd_Init();
   Lcd_Cmd(_LCD_CURSOR_OFF);
   Lcd_Cmd(_LCD_CLEAR);
   Lcd_Out(1, 1, "USB Gelen :");
   Lcd_Out(2, 1, "");

   HID_Enable(&readbuff,&writebuff);

   while(1){

      while(!HID_Read());

      text_kod = readbuff[0];
      text_uzunlugu = readbuff[1];

      if (text_kod == 0xAB)   // text ifade geldi
      {
         for (i = 2; i < text_uzunlugu + 2; i++)
            Lcd_Chr_Cp(readbuff[i]);
      }
      if (text_kod == 0xAD)   // LCD komutu geldi
      {
         if (readbuff[1] == 1) Lcd_Cmd(_LCD_CLEAR);
         if (readbuff[1] == 2) Lcd_Cmd(_LCD_FIRST_ROW);
         if (readbuff[1] == 3) Lcd_Cmd(_LCD_SECOND_ROW);
         if (readbuff[1] == 4) Lcd_Cmd(_LCD_CURSOR_OFF);
         if (readbuff[1] == 5) Lcd_Cmd(_LCD_UNDERLINE_ON);
         if (readbuff[1] == 6) Lcd_Cmd(_LCD_BLINK_CURSOR_ON);
         if (readbuff[1] == 7) Lcd_Cmd(_LCD_MOVE_CURSOR_LEFT);
         if (readbuff[1] == 8) Lcd_Cmd(_LCD_MOVE_CURSOR_RIGHT);
         if (readbuff[1] == 9) Lcd_Cmd(_LCD_SHIFT_LEFT);
         if (readbuff[1] == 10) Lcd_Cmd(_LCD_TURN_ON);
         if (readbuff[1] == 11) Lcd_Cmd(_LCD_TURN_OFF);
         if (readbuff[1] == 12) Lcd_Cmd(_LCD_SHIFT_RIGHT);
      }
  }
}