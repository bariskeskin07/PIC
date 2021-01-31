#include "USBdsc.c"

// LCD pin baðlantýlarý
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
// End LCD pin baðlantýlarý

unsigned char readbuff[64] absolute 0x500;
unsigned char writebuff[64] absolute 0x540;

const unsigned short ISI_bitleri = 12;

char cnt;
char *text = "000.0000";
unsigned ISI;

void interrupt(){
   USB_Interrupt_Proc();
}

void Display_Temperature(unsigned int temp2write) {
   const unsigned short bit_kaydir = ISI_bitleri - 8;
   char ISI_tam_deger;
   unsigned int ISI_kesirli;

  // Sýcaklýk sýfýrýn altýnda mý?
   if (temp2write & 0x8000) {
      text[0] = '-';
      temp2write = ~temp2write + 1;
      }

  // ISI_tam_deger elde ediliyor
   ISI_tam_deger = temp2write >> bit_kaydir ;

  // ISI_tam_deger karaktere dönüþtürülüyor
   if (ISI_tam_deger/100)
      text[0] = ISI_tam_deger/100  + 48;

   text[1] = (ISI_tam_deger/10)%10 + 48;             // Extract tens digit
   text[2] =  ISI_tam_deger%10     + 48;             // Extract ones digit

  // ISI_kesirli deðeri elde ediliyor
   ISI_kesirli  = temp2write << (4-bit_kaydir);
   ISI_kesirli &= 0x000F;
   ISI_kesirli *= 625;

  // ISI_kesirli karaktere dönüþtürülüyor
   text[4] =  ISI_kesirli/1000    + 48;         // Extract thousands digit
   text[5] = (ISI_kesirli/100)%10 + 48;         // Extract hundreds digit
   text[6] = (ISI_kesirli/10)%10  + 48;         // Extract tens digit
   text[7] =  ISI_kesirli%10      + 48;         // Extract ones digit

  // Isý LCD 'ye yazdýrýlýyor
   Lcd_Out(2, 5, text);
}

void main(){

   ADCON0 = 0;
   ADCON1 |= 0x0F;
   ADCON2 = 0;
   CMCON  |= 7;

   TRISE = 0xff;
   LATE = 0;
   PORTE = 0;
   
   Lcd_Init();
   Lcd_Cmd(_LCD_CLEAR);
   Lcd_Cmd(_LCD_CURSOR_OFF);
   Lcd_Out(1, 1, " DS18B20 ISI :   ");
  // Santigrat derece LCD 'ye yazýdýrýlýyor
   Lcd_Chr(2,13,223);
   Lcd_Chr(2,14,'C');

   HID_Enable(&readbuff,&writebuff);

  do {
    // Isý DS18B20 sensöründen okunuyor
    Ow_Reset(&PORTE, 2);
    Ow_Write(&PORTE, 2, 0xCC);
    Ow_Write(&PORTE, 2, 0x44);
    Delay_us(120);

    Ow_Reset(&PORTE, 2);
    Ow_Write(&PORTE, 2, 0xCC);
    Ow_Write(&PORTE, 2, 0xBE);

    ISI =  Ow_Read(&PORTE, 2);
    ISI = (Ow_Read(&PORTE, 2) << 8) + ISI;

    // LCD 'ye yazdýrmak için Isý deðeri ayarlanýyor
    Display_Temperature(ISI);
    
    for(cnt=0;cnt<64;cnt++)
      writebuff[cnt]=text[cnt];

    while(!HID_Write(&writebuff,64));

    Delay_ms(500);
  } while (1);
}