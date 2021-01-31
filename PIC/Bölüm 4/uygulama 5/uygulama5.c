#define  artir    PORTC.RC0
#define  azalt    PORTC.RC1

short display = 0;

void main() {
     ADCON1 |= 0x0F;
     CMCON  |= 7;

     trisb = 0;
     portb = 0;
     
     trisc = 0x03;
     portc = 0;

     while(1)
     {
        if (!artir)
        {
           display++;
           while(!artir);
        }
        if (!azalt)
        {
           display--;
           while(!azalt);
        }
        if ((display > 9) | (display < 0)) display = 0;
        portb = display;
     }
}