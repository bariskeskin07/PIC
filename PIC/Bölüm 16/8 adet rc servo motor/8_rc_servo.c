#include "built_in.h"                   // built_in.h dosyas� projemize ekleniyor
                                        // bit tipinde tan�mlanan de�i�kenlere
                                        // hi (1) yada lo (0) de�eri verebilmemiz i�in

#define   servo1        PORTD.RD0       // servo motorlar ve ba�l� bulunduklar�
#define   servo2        PORTD.RD1       // port pinleri tan�mlan�yor
#define   servo3        PORTD.RD2
#define   servo4        PORTD.RD3
#define   servo5        PORTD.RD4
#define   servo6        PORTD.RD5
#define   servo7        PORTD.RD6
#define   servo8        PORTD.RD7

// --- program i�erisinde kullan�lacak olan global de�i�kenler tan�mlan�yor ---
char secilen_motor = 1, secilen_hiz = 1, secilen_poz = 0;
unsigned poz;

const int rc_poz_limit = 12500;         // PWM maksimum limit = 2.5 ms x 8 = 20 ms
const int rc_poz_min = 2400;            // PWM minimum limit = 1.5 ms

unsigned servo_pwm[8] = {rc_poz_min, rc_poz_min, rc_poz_min,
                         rc_poz_min, rc_poz_min, rc_poz_min,
                         rc_poz_min, rc_poz_min};
unsigned short servo_idx = 0;
bit servo1_on;
bit servo2_on;
bit servo3_on;
bit servo4_on;
bit servo5_on;
bit servo6_on;
bit servo7_on;
bit servo8_on;
bit flag_phase;
unsigned rc_poz_interrupt = 53035;      // TMR1 i�in �n de�er

unsigned short tmp;
//-----------------------------------------------------------------------------

void interrupt()
{
   if (pir1.tmr1if)                     // tmr1 kesmesi olu�tu
   {
      if (!flag_phase)
      {
         if (servo_idx == 0 && servo1_on) servo1 = 1;
         if (servo_idx == 1 && servo2_on) servo2 = 1;
         if (servo_idx == 2 && servo3_on) servo3 = 1;
         if (servo_idx == 3 && servo4_on) servo4 = 1;
         if (servo_idx == 4 && servo5_on) servo5 = 1;
         if (servo_idx == 5 && servo6_on) servo6 = 1;
         if (servo_idx == 6 && servo7_on) servo7 = 1;
         if (servo_idx == 7 && servo8_on) servo8 = 1;
         rc_poz_interrupt = 65535 - servo_pwm[servo_idx];
         tmr1h = hi(rc_poz_interrupt);
         tmr1l = lo(rc_poz_interrupt);

      }
      if (flag_phase)
      {
         if (servo_idx == 0 && servo1_on) servo1 = 0;
         if (servo_idx == 1 && servo2_on) servo2 = 0;
         if (servo_idx == 2 && servo3_on) servo3 = 0;
         if (servo_idx == 3 && servo4_on) servo4 = 0;
         if (servo_idx == 4 && servo5_on) servo5 = 0;
         if (servo_idx == 5 && servo6_on) servo6 = 0;
         if (servo_idx == 6 && servo7_on) servo7 = 0;
         if (servo_idx == 7 && servo8_on) servo8 = 0;
         rc_poz_interrupt = 65535 - rc_poz_limit + servo_pwm[servo_idx];
         tmr1h = hi(rc_poz_interrupt);
         tmr1l = lo(rc_poz_interrupt);
         if (++servo_idx > 7) servo_idx = 0;
      }
      flag_phase = !flag_phase;
      pir1.TMR1IF = 0;
   }
}

void init()
{
    trisd = 0;                          // PORTD ��k�� olarak y�nlendirildi
    portd = 0;                          // PORTD s�f�rland�

    delay_ms(300);

    tmr1h = hi(rc_poz_interrupt);       // TMR1 i�in �n de�er y�klendi
    tmr1l = lo(rc_poz_interrupt);
    pie1.TMR1IE = 1;                    // TMR1 kesmesi aktif edildi
    t1con.TMR1ON = 1;                   // TMR1 zamanlay�c�s� �al��t�r�ld�
    RCON.IPEN = 0;                      // �evresel kesme maskelemeleri iptal edildi
    INTCON.GIE = 1;                     // Kesmeler aktif edildi
    INTCON.PEIE = 1;                    // �evresel kesmeler aktif edildi

    flag_phase = 0;
    servo1_on = 1;
    servo2_on = 1;
    servo3_on = 1;
    servo4_on = 1;
    servo5_on = 1;
    servo6_on = 1;
    servo7_on = 1;
    servo8_on = 1;

    servo1 = 0;                         // b�t�n servolar�n ctrl pinlerine
    servo2 = 0;                         // lojik 0 g�nderildi
    servo3 = 0;
    servo4 = 0;
    servo5 = 0;
    servo6 = 0;
    servo7 = 0;
    servo8 = 0;

    servo_pwm[0] = 2400;                // b�t�n servolar�n ba�lang�� pozisyonlar�
    servo_pwm[1] = 2400;                // -90 derece (ya da 0 derece) olarak
    servo_pwm[2] = 2400;                // belirlendi ( tam sol )
    servo_pwm[3] = 2400;
    servo_pwm[4] = 2400;
    servo_pwm[5] = 2400;
    servo_pwm[6] = 2400;
    servo_pwm[7] = 2400;
}

// servo motorlar� istenen pozisyona istenen h�z da getiren alt program
void pozisyon(unsigned short motor_no, unsigned poz, unsigned short hiz)
{
    unsigned short i;
    while(servo_pwm[motor_no] < poz)
    {
       servo_pwm[motor_no]++;
       for(i = 0; i < hiz; i++) delay_us(100);
    }
    while(servo_pwm[motor_no] > poz)
    {
       servo_pwm[motor_no]--;
       for(i = 0; i < hiz; i++) delay_us(100);
    }
}

void main() {                           // ana program

    init();                             // init() altprogram� �al��t�r�l�yor
    delay_ms(500);

    while(1)                            // sonsuz d�ng�
    {
       secilen_motor = 1;               // 1. servo motor se�ildi
       while(secilen_motor < 9)
       {
          delay_ms(100);
          poz = (55,56 * secilen_poz) + 2400;
          pozisyon((secilen_motor - 1), poz, secilen_hiz);
          secilen_motor++;
       }
       secilen_poz = secilen_poz + 45;  // servo pozisyonlar� 45 derece art�r�ld�
       if (secilen_poz > 180) secilen_poz = 0;      // pozisyon 180 ( ya da +90 )
    }                                               // dereceyi a�t� ise 0 derece
}                                                   // ye d�nder