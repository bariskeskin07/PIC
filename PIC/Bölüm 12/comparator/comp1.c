
void main() {

   trisa = 0x0f;         // RA3:RA0 giriþ, diðerleri çýkýþ
   porta = 0;            // PORTA sýfýrlandý

   cmcon = 0x05;         // Ýki baðýmsýz karþýlaþtýrýcý modu (CM2:CM0 = 101)

   while(1);             // sonsuz döngü

}