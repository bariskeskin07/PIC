#include        "_T6963C.h"
#include        "ata.c"
#include        "ceyda.c"
#include        "elif.c"

// T6963C grafik LCD baðlantýsý
char T6963C_dataPort at PORTD;                   // DATA port

sbit T6963C_ctrlwr  at LATB2_bit;                // WR write signal
sbit T6963C_ctrlrd  at LATB1_bit;                // RD read signal
sbit T6963C_ctrlcd  at LATB0_bit;                // CD command/data signal
sbit T6963C_ctrlrst at LATB4_bit;                // RST reset signal
sbit T6963C_ctrlwr_Direction  at TRISB2_bit;     // WR write signal
sbit T6963C_ctrlrd_Direction  at TRISB1_bit;     // RD read signal
sbit T6963C_ctrlcd_Direction  at TRISB0_bit;     // CD command/data signal
sbit T6963C_ctrlrst_Direction at TRISB4_bit;     // RST reset signal

sbit T6963C_ctrlce at LATB3_bit;                 // CE signal
sbit T6963C_ctrlfs at LATB6_bit;                 // FS signal
sbit T6963C_ctrlmd at LATB5_bit;                 // MD signal
sbit T6963C_ctrlce_Direction  at TRISB3_bit;     // CE signal direction
sbit T6963C_ctrlfs_Direction  at TRISB6_bit;     // FS signal direction
sbit T6963C_ctrlmd_Direction  at TRISB5_bit;     // MD signal direction
// End T6963C grafik LCD baðlantýsý

void main() {

  char txt1[] = "      MikroC & PIC18F4550    ";
  char txt[] =  "GLCD KUTUPHANESiNE HOSGELDiNiZ";

  ADCON1 |= 0x0F;               // AN pinleri dijital giriþ/çýkýþ
  CMCON  |= 7;                  // komparatorler disable edildi

  T6963C_ctrlce_Direction = 0;
  T6963C_ctrlce = 0;            // T6963C grafik LCD Enable edildi
  T6963C_ctrlfs_Direction = 0;
  T6963C_ctrlfs = 0;            // 8x8 Font seçildi
  T6963C_ctrlmd_Direction = 0;
  T6963C_ctrlmd = 0;            // sütun sayýsý seçildi

  T6963C_init(240, 128, 8);     // T6963C yapýlandýrýldý

  T6963C_graphics(1);           // Grafik ve text mode ikisi birlikte
  T6963C_text(1);               // seçilerek aktif edildi

  // Text mesajlar LCD'ye gönderiliyor
  T6963C_write_text(txt, 0, 0, T6963C_ROM_MODE_XOR);
  T6963C_write_text("Sivas EML Elektronik", 5, 7, T6963C_ROM_MODE_XOR);
  T6963C_write_text(txt1, 0, 15, T6963C_ROM_MODE_XOR);
  
  // kutular çizdiriliyor
  T6963C_box(0, 0, 239, 8, T6963C_WHITE);
  T6963C_box(0, 53, 239, 67, T6963C_WHITE);
  T6963C_box(0, 119, 239, 127, T6963C_WHITE);

  // dikdörtgenler çizdiriliyor
  T6963C_rectangle(20, 20, 219, 107, T6963C_WHITE);
  T6963C_rectangle(40, 40, 199, 87, T6963C_WHITE);

  T6963C_box(0, 56, 239, 64, T6963C_BLACK);

  // yuvarlak kenarlý dikdörtgen çizdiriliyor
  T6963C_Rectangle_Round_Edges(10, 10, 229, 117, 12, T6963C_WHITE);

  // içi dolu yuvarlak kenarlý dikdörtgenler çizdiriliyor
  T6963C_Rectangle_Round_Edges_Fill(10, 10, 229, 117, 12, T6963C_WHITE);
  T6963C_Rectangle_Round_Edges_Fill(20, 20, 219, 107, 12, T6963C_BLACK);
  T6963C_Rectangle_Round_Edges_Fill(30, 30, 209, 97, 12, T6963C_WHITE);

  T6963C_graphics(1);              // grafik mode seçildi
  T6963C_text(0);                  // text mode disable edildi
  delay_ms(500);
  T6963C_graphics(0);              // grafik mode disable edildi
  T6963C_text(1);                  // text mode seçildi
  delay_ms(500);
  T6963C_graphics(1);              // grafik mode ve text mode ikisi birlikte
  T6963C_text(1);                  // seçildi
  
  T6963C_init(240, 128, 8);        // ekraný silmek için kullanýldý
  T6963C_graphics(1);              // grafik mode ve text mode ikisi birlikte
  T6963C_text(1);                  // seçildi

  T6963C_sprite(75, 0, ata, 90, 118) ;   // x ekseninde 75. ve y ekseninde 0.
  delay_ms(1000);                        // pikselden baþlayarak resmi ekrana bas
                                         // resmin eni 90, boyu 118 piksel
  T6963C_sprite(36, 0, elif, 170, 128) ; // x ekseninde 36. ve y ekseninde 0.
  delay_ms(1000);                        // pikselden baþlayarak resmi ekrana bas
                                         // resmin eni 170, boyu 128 piksel
  T6963C_sprite(25, 0, ceyda, 192, 128) ;
}