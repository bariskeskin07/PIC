#include "USBdsc.c"

unsigned char readbuff[64] absolute 0x500;   // Buffers should be in USB RAM, please consult datasheet
unsigned char writebuff[64] absolute 0x540;

char cnt;

void interrupt(){
   USB_Interrupt_Proc();                   // USB servicing is done inside the interrupt
}

void main(void){
  ADCON1 |= 0x0F;                         // Configure all ports with analog function as digital
  CMCON  |= 7;                            // Disable comparators
  trisb = 0;
  portb = 0;

  HID_Enable(&readbuff,&writebuff);       // Enable HID communication

  while(1){
     while(!HID_Read());

//     for(cnt=0;cnt<64;cnt++)
//       writebuff[cnt]=readbuff[cnt];

     portb = readbuff[0];
  }
}