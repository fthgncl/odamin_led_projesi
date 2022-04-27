
unsigned long oldTime = 0;
unsigned long nowTime = 0;
#define nextCloudDelay 5000
int grup = 0;

void partly_cloudy() {
  nowTime = millis();
  byte color[3] = { random(50), random(50), random(50) };
  if ( nowTime - oldTime > nextCloudDelay ) {
    oldTime = nowTime;
    isikVer(grup, grup+random(1,3), color,random(5,20));
    grup++;
  }
}

int baslangicDegerleriniHesapla(int grupNo, int ledAdeti = 25) {

  int grupSayisi = NUM_LEDS / ledAdeti;
  while (grupNo > grupSayisi)
    grupNo -= grupSayisi;

  return grupNo * ledAdeti;

}
void isikVer(int BaslangicGrupNo, int BitislangicGrupNo, byte renk[3],int ledAdeti) {
  int baslangic = baslangicDegerleriniHesapla(BaslangicGrupNo,ledAdeti);
  int bitis = baslangicDegerleriniHesapla(BitislangicGrupNo,ledAdeti);
  for ( int i = baslangic ; i < bitis ; i++ ) {
    leds[i].setRGB(renk[0], renk[1], renk[2]);
  }
}
