
void main() {

   trisa = 0x0f;         // RA3:RA0 giri�, di�erleri ��k��
   porta = 0;            // PORTA s�f�rland�

   cmcon = 0x05;         // �ki ba��ms�z kar��la�t�r�c� modu (CM2:CM0 = 101)

   while(1);             // sonsuz d�ng�

}