void interrupt()
{
   if (CCP1IF) portb.rb7 = 1;
   CCP1IF_bit = 0;        // CCP1IF bayra�� temizlendi
}

void main() {

  ADCON1 |= 0x0F;         // AN pinleri dijital I/O yap�land�r�ld�
  CMCON  |= 7;            // Comparators (kar��la�t�r�c�lar) pasif edildi

  TRISB = 0x00;           // PORTB ��k�� yap�ld�
  PORTB = 0x00;           // PORTB temizlendi
  
  TRISC.RC0 = 1;          // RC0/T13CKI pini giri� yap�ld�.
  PORTC.RC0 = 1;          // RC0/T13CKI pini 1 yap�ld�.

  TMR1L = 0x00;           // TMR1L ve TMR1H kaydedici �ifti s�f�rland�
  TMR1H = 0x00;
  T1CON = 0x33;           // TMR1 1:8 prescaler ve T13CKI giri�inden gelen
                          // her 8. y�kselen darbe kenar�nda 1 artmaya ayarland�

  CCPR1L = 0x03;          // TMR1 ile CCPR kar��la�t�rmas� i�in CCPR1L = 0x03
  CCPR1H = 0x00;          // de�eri y�klendi.
  CCP1CON = 0x0B;         // CCP1 donan�m� Compare modu, �zel tetikleme modu
  CCP1IE_bit = 1;         // CCP1 donan�m� aktif edildi.

  INTCON = 0xC0;          // GIE, PEIE bitleri set edildi

  while(1);               // Sonsuz d�ng�.
  
}