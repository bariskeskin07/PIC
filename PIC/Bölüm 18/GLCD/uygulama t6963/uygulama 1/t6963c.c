#include        "___T6963C.h"

// T6963C module connections
char T6963C_dataPort at PORTD;                   // DATA port

sbit T6963C_ctrlwr  at LATB2_bit;                // WR write signal
sbit T6963C_ctrlrd  at LATB1_bit;                // RD read signal
sbit T6963C_ctrlcd  at LATB0_bit;                // CD command/data signal
sbit T6963C_ctrlrst at LATB4_bit;                // RST reset signal
sbit T6963C_ctrlwr_Direction  at TRISB2_bit;     // WR write signal
sbit T6963C_ctrlrd_Direction  at TRISB1_bit;     // RD read signal
sbit T6963C_ctrlcd_Direction  at TRISB0_bit;     // CD command/data signal
sbit T6963C_ctrlrst_Direction at TRISB4_bit;     // RST reset signal

// Signals not used by library, they are set in main function
sbit T6963C_ctrlce at LATB3_bit;                 // CE signal
sbit T6963C_ctrlfs at LATB6_bit;                 // FS signal
sbit T6963C_ctrlmd at LATB5_bit;                 // MD signal
sbit T6963C_ctrlce_Direction  at TRISB3_bit;     // CE signal direction
sbit T6963C_ctrlfs_Direction  at TRISB6_bit;     // FS signal direction
sbit T6963C_ctrlmd_Direction  at TRISB5_bit;     // MD signal direction
// End T6963C module connections

void main() {

  #define LINE_DEMO             // Uncomment to demonstrate line drawing routines
  #define FILL_DEMO           // Uncomment to demonstrate fill routines
  #define PARTIAL_IMAGE_DEMO  // Uncomment to demonstrate partial image routine

  //char txt1[] = " EINSTEIN WOULD HAVE LIKED mE";
  char txt1[] = "      MikroC & PIC18F4550    ";
  char txt[] =  "GLCD KUTUPHANESiNE HOSGELDiNiZ";
  //char txt[] =  " GLCD LIBRARY DEMO, WELCOME !";
  //char txt2[] = " Partial image demo!";

  unsigned char  panel;         // Current panel
  unsigned int   i;             // General purpose register
  unsigned char  curs;          // Cursor visibility
  unsigned int   cposx, cposy;  // Cursor x-y position

  ADCON1 |= 0x0F;               // Configure AN pins as digital
  CMCON  |= 7;                  // Disable comparators

  TRISC0_bit = 1;               // Set RB0 as input
  TRISC1_bit = 1;               // Set RB1 as input
  TRISC2_bit = 1;               // Set RB2 as input
  /*TRISB3_bit = 1;               // Set RB3 as input
  TRISB4_bit = 1;               // Set RB4 as input
  TRISB5_bit = 1;               // Set RB5 as input*/

  T6963C_ctrlce_Direction = 0;
  T6963C_ctrlce = 0;            // Enable T6963C
  T6963C_ctrlfs_Direction = 0;
  T6963C_ctrlfs = 0;            // Font Select 8x8
  T6963C_ctrlmd_Direction = 0;
  T6963C_ctrlmd = 0;            // Column number select

  panel = 0;
  i = 0;
  curs = 0;
  cposx = cposy = 0;

  // Initialize T6963C
  T6963C_init(240, 128, 8);

  /*
   * Enable both graphics and text display at the same time
   */
  T6963C_graphics(1);
  T6963C_text(1);

  /*
   * Text messages
   */
  T6963C_write_text(txt, 0, 0, T6963C_ROM_MODE_XOR);
  T6963C_write_text(txt1, 0, 15, T6963C_ROM_MODE_XOR);

  /*
   * Cursor
   */
  T6963C_cursor_height(8);       // 8 pixel height
  T6963C_set_cursor(0, 0);       // Move cursor to top left
  T6963C_cursor(0);              // Cursor off

  /*
   * Draw solid boxes
   */
  T6963C_box(0, 0, 239, 8, T6963C_WHITE);
  T6963C_box(0, 119, 239, 127, T6963C_WHITE);

  /*
   * Draw rectangles
   */
  #ifdef LINE_DEMO
    T6963C_rectangle(0, 0, 239, 127, T6963C_WHITE);
    T6963C_rectangle(20, 20, 219, 107, T6963C_WHITE);
    T6963C_rectangle(40, 40, 199, 87, T6963C_WHITE);
    T6963C_rectangle(60, 60, 179, 67, T6963C_WHITE);
  #endif

  /*
   * Draw rounded edge rectangle
   */
  #ifdef LINE_DEMO
    T6963C_Rectangle_Round_Edges(10, 10, 229, 117, 12, T6963C_WHITE);
    T6963C_Rectangle_Round_Edges(30, 30, 209, 97, 12, T6963C_WHITE);
    T6963C_Rectangle_Round_Edges(50, 50, 189, 77, 12, T6963C_WHITE);
  #endif

  /*
   * Draw filled rounded edge rectangle
   */
  #ifdef FILL_DEMO
    T6963C_Rectangle_Round_Edges_Fill(10, 10, 229, 117, 12, T6963C_WHITE);
    T6963C_Rectangle_Round_Edges_Fill(20, 20, 219, 107, 12, T6963C_BLACK);
    T6963C_Rectangle_Round_Edges_Fill(30, 30, 209, 97, 12, T6963C_WHITE);
    T6963C_Rectangle_Round_Edges_Fill(40, 40, 199, 87, 12, T6963C_BLACK);
    T6963C_Rectangle_Round_Edges_Fill(50, 50, 189, 77, 12, T6963C_WHITE);
  #endif

  /*
   * Draw a cross
   */
  #ifdef LINE_DEMO
    T6963C_line(0, 0, 239, 127, T6963C_WHITE);
    T6963C_line(0, 127, 239, 0, T6963C_WHITE);
  #endif

  /*
   * Draw circles
   */
  #ifdef LINE_DEMO
    T6963C_circle(120, 64, 10, T6963C_WHITE);
    T6963C_circle(120, 64, 30, T6963C_WHITE);
    T6963C_circle(120, 64, 50, T6963C_WHITE);
    T6963C_circle(120, 64, 70, T6963C_WHITE);
    T6963C_circle(120, 64, 90, T6963C_WHITE);
    T6963C_circle(120, 64, 110, T6963C_WHITE);
    T6963C_circle(120, 64, 130, T6963C_WHITE);
  #endif

  /*
   * Draw filled circles
   */
  #ifdef FILL_DEMO
    T6963C_circle_fill(120, 64, 60, T6963C_WHITE);
    T6963C_circle_fill(120, 64, 55, T6963C_BLACK);
    T6963C_circle_fill(120, 64, 50, T6963C_WHITE);
    T6963C_circle_fill(120, 64, 45, T6963C_BLACK);
    T6963C_circle_fill(120, 64, 40, T6963C_WHITE);
    T6963C_circle_fill(120, 64, 35, T6963C_BLACK);
    T6963C_circle_fill(120, 64, 30, T6963C_WHITE);
    T6963C_circle_fill(120, 64, 25, T6963C_BLACK);
    T6963C_circle_fill(120, 64, 20, T6963C_WHITE);
    T6963C_circle_fill(120, 64, 15, T6963C_BLACK);
    T6963C_circle_fill(120, 64, 10, T6963C_WHITE);
    T6963C_circle_fill(120, 64, 5, T6963C_BLACK);
  #endif

  Delay_ms(1000);
  //T6963C_sprite(76, 4, einstein, 88, 119);         // Draw a sprite
  Delay_ms(1000);

  T6963C_setGrPanel(1);                            // Select other graphic panel
  //T6963C_image(mikroE_240x128_bmp);
  T6963C_displayGrPanel(1);
  Delay_ms(1000);
  #ifdef PARTIAL_IMAGE_DEMO
    T6963C_grFill(0);
    //T6963C_PartialImage(0, 0, 64, 64, 240, 128, mikroE_240x128_bmp);  // Display partial image
    Delay_ms(1000);
    T6963C_graphics(0);
    //T6963C_image(mikroE_240x128_bmp);
  #endif
  T6963C_graphics(1);
  T6963C_displayGrPanel(0);

  for(;;) {                                          // Endless loop

    /*
     * If RB0 is pressed, display only graphic panel
     */
    if(RC0_bit) {
      T6963C_graphics(1);
      T6963C_text(0);
      Delay_ms(300);
    }

    /*
     * If RB1 is pressed, toggle the display between graphic panel 0 and graphic panel 1
     */
    else if(RC1_bit) {
      panel++;
      panel &= 1;
      T6963C_displayGrPanel(panel);
      Delay_ms(300);
    }

    /*
     * If RB2 is pressed, display only text panel
     */
    else if(RC2_bit) {
      T6963C_graphics(0);
      T6963C_text(1);
      Delay_ms(300);
    }

    /*
     * If RB3 is pressed, display text and graphic panels
     */
    else if(RB3_bit) {
      T6963C_graphics(1);
      T6963C_text(1);
      Delay_ms(300);
    }

    /*
     * If RB4 is pressed, change cursor
     */
    else if(RB4_bit) {
      curs++;
      if(curs == 3) curs = 0;
      switch(curs) {
        case 0:
          // no cursor
          T6963C_cursor(0);
          break;
        case 1:
          // blinking cursor
          T6963C_cursor(1);
          T6963C_cursor_blink(1);
          break;
        case 2:
          // non blinking cursor
          T6963C_cursor(1);
          T6963C_cursor_blink(0);
          break;
        }
      Delay_ms(300);
      }

    #ifdef PARTIAL_IMAGE_DEMO
    /*
     * If RB5 is pressed, perform the "Partial image" demostration
     */
     else if(RB5_bit) {
       T6963C_setGrPanel(0);
       T6963C_setTxtPanel(0);
       T6963C_txtFill(0);
       T6963C_setGrPanel(1);
       T6963C_setTxtPanel(0);
       T6963C_graphics(1);
       T6963C_text(1);
       T6963C_displayGrPanel(1);
//       T6963C_write_text(txt2, 5, 15, T6963C_ROM_MODE_XOR);
       Delay_1sec();

       T6963C_grFill(0);
       //T6963C_PartialImage(0, 0, 64, 64, 240, 128, mikroE_240x128_bmp);
       Delay_1sec();

       //T6963C_PartialImage(0, 0, 128, 128, 240, 128, mikroE_240x128_bmp);
       Delay_1sec();

       //T6963C_PartialImage(0, 0, 240, 128, 240, 128, mikroE_240x128_bmp);
       Delay_1sec();

       T6963C_txtFill(0);
       T6963C_write_text(txt, 0, 0, T6963C_ROM_MODE_XOR);
       T6963C_write_text(txt1, 0, 15, T6963C_ROM_MODE_XOR);
    }
    #endif

    /*
     * Move cursor, even if not visible
     */
    cposx++;
    if(cposx == T6963C_txtCols) {
      cposx = 0;
      cposy++;
      if(cposy == T6963C_grHeight / T6963C_CHARACTER_HEIGHT) {
        cposy = 0;
        }
      }
    T6963C_set_cursor(cposx, cposy);

    Delay_ms(100);
    }
}