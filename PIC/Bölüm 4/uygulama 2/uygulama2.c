void main() {
     ADCON1 |= 0x0F;
     CMCON  |= 7;

     trisb = 0;
     portb = 0;

     while(1)
     {
        portb = ~portb;
        delay_ms(500);
     }
}