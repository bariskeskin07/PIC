const char display[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66,
	                   0x6D, 0x7D, 0x07, 0x7F, 0x6F };
unsigned short i = 9;

void main() {
     ADCON1 |= 0x0F;
     CMCON  |= 7;

     trisb = 0;
     portb = 1;

     while(1)
     {
        for(i=0; i<10; i++)
        {
           portb = display[i];
           delay_ms(300);
        }
        for(i = 10; i > 0; i--)
        {
           portb = display[i-1];
           delay_ms(300);
        }
     }
}