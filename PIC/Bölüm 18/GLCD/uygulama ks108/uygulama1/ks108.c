#include "busra.c"

// Glcd display baðlantýlarý
char GLCD_DataPort at PORTD;                // data pinleri baðlantýsý

sbit GLCD_CS1 at LATB0_bit;                 // CS1 pini RB0'a
sbit GLCD_CS2 at LATB1_bit;                 // CS2 pini RB1'e
sbit GLCD_RS  at LATB2_bit;                 // RS pini RB2'ye
sbit GLCD_RW  at LATB3_bit;                 // RW pini RB3'e
sbit GLCD_EN  at LATB4_bit;                 // EN pini RB4'e
sbit GLCD_RST at LATB5_bit;                 // RST pini RB5'e

sbit GLCD_CS1_Direction at TRISB0_bit;
sbit GLCD_CS2_Direction at TRISB1_bit;
sbit GLCD_RS_Direction  at TRISB2_bit;
sbit GLCD_RW_Direction  at TRISB3_bit;
sbit GLCD_EN_Direction  at TRISB4_bit;
sbit GLCD_RST_Direction at TRISB5_bit;
// End Glcd display baðlantýlarý

void main() {

  ADCON1 |= 0x0F;         // AN pinleri dijital giriþ/çýkýþ
  CMCON  |= 7;            // komparatörler disable edildi

  Glcd_Init();            // KS108 GLCD yapýlandýrýldý
  Glcd_Fill(0x00);        // ekran temizlendi


  while(1) {

    Glcd_Write_Text("KS108 GLCD UYGULAMASI ", 0, 0, 1);      // text ekrana
    Glcd_Write_Text(" MikroC & PIC18F4550  ", 0, 3, 1);      // gönderiliyor
    Glcd_Write_Text("Sivas EML Elektronik  ", 0, 7, 1);      //
    delay_ms(1000);
  
    Glcd_Image(busra);                     // resim ekrana basýlýyor
    delay_ms(1000);
    
    Glcd_Box(0, 0, 127, 63, 0);            // ekrana kutu çiziliyor
    delay_ms(1000);
    
    Glcd_Line(0, 0, 127, 63, 1);           // çizgi çiziliyor
    Glcd_Line(127, 0, 0, 63, 1);           // çizgi çiziliyor
    delay_ms(1000);
    Glcd_Box(0, 0, 127, 63, 0);            // ekraný temizleme amaçlý kutu
    
  }
}