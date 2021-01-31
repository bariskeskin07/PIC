// LCD module baðlantýlarý
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
// End LCD module baðlantýlarý

// global deðiþkenler tanýmlanýyor
unsigned say = 0;
unsigned gelen_data, bit_say;

enum {
        sinyal_yok,
        Start_bit,
        alinan_bit
};

char aktif_durum = sinyal_yok;
char data_var = 0;
char komut_kodu, cihaz_kodu;
char txt[4];

// kesme alt programý
void interrupt(){
     if(INTCON.INT0IF){
        switch (aktif_durum){
           case sinyal_yok:
                      INTCON2.INTEDG0 = 1;        //interrupt yükselen kenarda
                      say = 0;
                      aktif_durum = Start_bit;
                      break;
           //yükselen kenar bulundu, uzunluðu 2.4ms mi kontrol ediliyor
           case Start_bit:
                      //doðru sinyal
                      if(say == 4) {
                         say = 0;
                         bit_say = 0;
                         gelen_data = 0;
                         aktif_durum = alinan_bit;
                         } else {
                            //hatalý sinyal
                            aktif_durum = sinyal_yok;
                         }
                      break;
           case alinan_bit:
                      //sinyalin uzunluðu kontrol ediliyor (0 veya 1)
                      if(say == 2){
                         gelen_data >>= 1;         // lojik 0 (alýnan veriye ekle)
                         bit_say++;
                      }else {
                         if(say == 3){
                            gelen_data >>= 1;
                            gelen_data |= 0x8000;  //lojik 1 (alýnan veriye ekle)
                            bit_say++;
                         } else {
                            //hata oluþursa
                            INTCON2.INTEDG0 = 0;    //interrupt on falling edge.
                            aktif_durum = sinyal_yok;
                         }
                       }
                      //12-bit
                      if(bit_say >= 12){
                         data_var = 1;
                         gelen_data >>= 4;
                         INTCON2.INTEDG0 = 0;      //interrupt düþen kenarda
                         aktif_durum = sinyal_yok;
                      }
                      say = 0;
                      break;
            default: aktif_durum = sinyal_yok;
        }
     INTCON.INT0IF = 0;       //interrupt bayraðý sýfýrlandý
     }
     if (tmr2if_bit){
        say++;
        if(say > 5) {
            aktif_durum = sinyal_yok;
            say = 0;
            INTCON2.INTEDG0 = 0;        //interrupt düþen kenarda
        }
        portc.rc0 = !portc.rc0;
        TMR2IF_bit = 0;          //interrupt bayraðý sýfýrlandý
     }
}

void main() {
     TRISC = 0;                  //portc çýkýþ yapýldý
     TRISB = 0;                  //portb çýkýþ yapýldý
// RB0 interrupt set up
     INTCON.INT0IE = 1;          //RB0 interrupt aktif edildi
     INTCON2.INTEDG0 = 0;        //interrupt düþen kenarda
     TRISB.RB0 = 1;              //RB0 = giriþ yapýldý
     ADCON1 = 0x0F;              //A/D pinleri dijital I/O
// Timer2 interrupt set edildi, interrupt her 600us için ayarlandý
     T2CON = 0x01;               //timer kapalý, prescaler 1:16
     PR2 = 150;                  //preload timer2 karþýlaþtýrýcý deðeri
     TMR2 = 0;                   //timer2 resetlendi
     PIR1.TMR2IF = 0;            //interrupt bayraðý sýfýrlandý
     PIE1.TMR2IE = 1;            //timer2 interrupt'ý aktif edildi

     IPR1.TMR2IP = 1;            //timer2 interrupt yüksek öncelikli
// Bütün çevresel interruptlar aktif
     INTCON.PEIE = 1;
     INTCON.GIE = 1;

     T2CON.TMR2ON = 1;           // timer2 açýk

     Lcd_Init();
     Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Out(1, 1, "Cihaz kod:");
     Lcd_Out(2, 1, "komut kod:");

     while(1){
     if(data_var){
            komut_kodu = gelen_data & 0x7F;  // komut kodu elde ediliyor
            cihaz_kodu = gelen_data >> 7;    // cihaz kodu elde ediliyor
            data_var = 0;
            if(cihaz_kodu == 1){             // cihaz TV ise
               ByteToStr(cihaz_kodu, txt);
               Lcd_Out(1, 11, txt);        // LCD'ye cihaz kodu yazdýrýlýyor
               ByteToStr(komut_kodu, txt);
               Lcd_Out(2, 11, txt);        // LCD'ye komut kodu yazdýrýlýyor
               PIE1.TMR2IE = 0;            // timer2 interrupt pasif edildi
               Delay_ms(100);
               TMR2 = 0;                   // timer2 sýfýrlandý
               PIE1.TMR2IE = 1;            // timer2 interrupt aktif edildi
            }
          }
     }

}