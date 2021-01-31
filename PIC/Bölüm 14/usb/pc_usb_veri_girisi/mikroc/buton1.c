#include "USBdsc.c"

unsigned char readbuff[64] absolute 0x500;
unsigned char writebuff[64] absolute 0x540;

//char cnt;

void interrupt(){
   USB_Interrupt_Proc();
}

void main(){

   ADCON0 = 0;
   ADCON1 |= 0x0F;
   ADCON2 = 0;
   CMCON  |= 7;
   
   TRISE = 0xff;
   LATE = 0;
   PORTE = 0;

   HID_Enable(&readbuff,&writebuff);

   while(1){

      while(!HID_Read())
     {
        if (!porte.RE0) writebuff[2] = 1; else writebuff[2] = 0;
        if (!porte.RE1) writebuff[3] = 1; else writebuff[3] = 0;
        while(!HID_Write(&writebuff,64));
     }
     
  }
}