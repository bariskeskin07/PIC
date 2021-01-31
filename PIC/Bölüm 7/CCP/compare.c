void interrupt()
{
   if (CCP1IF) portb.rb7 = 1;
   CCP1IF_bit = 0;        // CCP1IF bayraðý temizlendi
}

void main() {

  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yapýlandýrýldý
  CMCON  |= 7;            // Comparators (karþýlaþtýrýcýlar) pasif edildi

  TRISB = 0x00;           // PORTB çýkýþ yapýldý
  PORTB = 0x00;           // PORTB temizlendi
  
  TRISC.RC0 = 1;          // RC0/T13CKI pini giriþ yapýldý.
  PORTC.RC0 = 1;          // RC0/T13CKI pini 1 yapýldý.

  TMR1L = 0x00;           // TMR1L ve TMR1H kaydedici çifti sýfýrlandý
  TMR1H = 0x00;
  T1CON = 0x33;           // TMR1 1:8 prescaler ve T13CKI giriþinden gelen
                          // her 8. yükselen darbe kenarýnda 1 artmaya ayarlandý

  CCPR1L = 0x03;          // TMR1 ile CCPR karþýlaþtýrmasý için CCPR1L = 0x03
  CCPR1H = 0x00;          // deðeri yüklendi.
  CCP1CON = 0x0B;         // CCP1 donanýmý Compare modu, özel tetikleme modu
  CCP1IE_bit = 1;         // CCP1 donanýmý aktif edildi.

  INTCON = 0xC0;          // GIE, PEIE bitleri set edildi

  while(1);               // Sonsuz döngü.
  
}