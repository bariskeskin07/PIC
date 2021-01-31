void main() {
     ADCON1 |= 0x0F;
     CMCON  |= 7;

     trisb = 0;
     portb = 1;

     trisd.rd0 = 1;
     portd.rd0 = 0;

     while(1)
     {
        if (portd.rd0) {
           portb <<= 1;
           while(portd.rd0);
        }
     }
}