
#define         input1          portc.rc0
#define         input2          portc.rc1
#define         enable_a        portc.rc2
#define         enable_b        portc.rc3
#define         ileri           portb.rb0
#define         geri            portb.rb1
#define         hizli_stop      portb.rb2

void init()
{
   ADCON1 |= 0x0F;             // AN pinleri dijital I/O yapýlandýrýldý
   CMCON  |= 7;                // Comparators (karþýlaþtýrýcýlar) pasif edildi

   trisc = 0;                  // C portu çýkýþ yapýldý
   portc = 0;                  // C portu sýfýrlandý
   enable_a = 1;               // L298'in A köprüsü seçildi
}

void main() {
   init();
   
   while(1)
   {
      if (ileri) {             // ileri butonuna basýldý ise
         input1 = 1;
         input2 = 0;
      }
      if (geri) {              // geri butonuna basýldý ise
         input1 = 0;
         input2 = 1;
      }
      if (hizli_stop) {        // stop butonuna basýldý ise
         input1 = 0;
         input2 = 0;
      }
   }
}