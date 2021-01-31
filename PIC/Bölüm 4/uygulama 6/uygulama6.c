//#define  artir    PORTC.RC0
//#define  azalt    PORTC.RC1

short display = 0;

void main() {
     ADCON1 |= 0x0F;
     CMCON  |= 7;

     trisb = 0;
     portb = 0;

//     trisc = 0x03;
//     portc = 0;

     while(1)
     {
        portb = dec2bcd(display);
        display++;
        delay_ms(250);
        if (display > 99) display = 0;
     }
}