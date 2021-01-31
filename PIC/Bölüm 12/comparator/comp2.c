void interrupt()
{
   if (cmif_bit)
   {
      if (!cis_bit)      // RA0 ve RA1 giri�leri se�ili ise
      {
         if (c1out_bit) portb.rb0 = 0; else portb.rb0 = 1;
         if (c2out_bit) portb.rb1 = 0; else portb.rb1 = 1;
      }
      if (cis_bit)       // RA2 ve RA3 giri�leri se�ili ise
      {
         if (c1out_bit) portb.rb3 = 0; else portb.rb3 = 1;
         if (c2out_bit) portb.rb2 = 0; else portb.rb2 = 1;
      }
   }
   cmif_bit = 0;         // Kar��la�t�r�c� kesme bayra�� s�f�rland�
}

void main() {

   trisa = 0x0f;         // RA3:RA0 giri�, di�erleri ��k��
   porta = 0;            // PORTA s�f�rland�
   
   trisb = 0;            // PORTB ��k�� olarak y�nlendirildi
   portb = 0;            // PORTB s�f�rland�
   
   cmie_bit = 1;         // Kar��la�t�r�c� kesmesi aktif edildi
   cmcon = 0x06;         // �ki ba��ms�z kar��la�t�r�c� modu (CM2:CM0 = 110)
   cvrcon = 0xaf;        // Dahili voltaj referans mod�l� aktif edildi
                         // 3.125 volt olarak ayarland�
   intcon = 0xc0;        // �evresel kesmeler aktif edildi

   while(1)              // sonsuz d�ng�
   {
      cis_bit = 0;       // RA0 ve RA1 giri�leri se�ildi
      delay_us(1);       // 1 us bekle
      cis_bit = 1;       // RA2 ve RA3 giri�leri se�ildi
   }

}