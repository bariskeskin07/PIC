void main() {
     ADCON1 |= 0x0F;
     CMCON  |= 7;

     trisb = 0;
     portb = 0;

     while(1)
     {
        do {
           portb++;
           delay_ms(200);
        } while (portb < 255);
        delay_ms(1000);
        do {
           portb--;
           delay_ms(200);
        } while (portb > 0);
        delay_ms(1000);
     }
}