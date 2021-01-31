void interrupt()
{
   if (cmif_bit)
   {
      if (!cis_bit)      // RA0 ve RA1 giriþleri seçili ise
      {
         if (c1out_bit) portb.rb0 = 0; else portb.rb0 = 1;
         if (c2out_bit) portb.rb1 = 0; else portb.rb1 = 1;
      }
      if (cis_bit)       // RA2 ve RA3 giriþleri seçili ise
      {
         if (c1out_bit) portb.rb3 = 0; else portb.rb3 = 1;
         if (c2out_bit) portb.rb2 = 0; else portb.rb2 = 1;
      }
   }
   cmif_bit = 0;         // Karþýlaþtýrýcý kesme bayraðý sýfýrlandý
}

void main() {

   trisa = 0x0f;         // RA3:RA0 giriþ, diðerleri çýkýþ
   porta = 0;            // PORTA sýfýrlandý
   
   trisb = 0;            // PORTB çýkýþ olarak yönlendirildi
   portb = 0;            // PORTB sýfýrlandý
   
   cmie_bit = 1;         // Karþýlaþtýrýcý kesmesi aktif edildi
   cmcon = 0x06;         // Ýki baðýmsýz karþýlaþtýrýcý modu (CM2:CM0 = 110)
   cvrcon = 0xaf;        // Dahili voltaj referans modülü aktif edildi
                         // 3.125 volt olarak ayarlandý
   intcon = 0xc0;        // Çevresel kesmeler aktif edildi

   while(1)              // sonsuz döngü
   {
      cis_bit = 0;       // RA0 ve RA1 giriþleri seçildi
      delay_us(1);       // 1 us bekle
      cis_bit = 1;       // RA2 ve RA3 giriþleri seçildi
   }

}