void main() {
     trisb.rb0 = 0;
     portb.rb0 = 0;
     
     while(1)
     {
        portb.rb0 = 0;
        delay_ms(1000);
        portb.rb0 = 1;
        delay_ms(1000);
     }
}