unsigned long rotaHesaplamaZamani = 0;
unsigned long simdikiZaman = 0;
#define YOL_ADETI 10
#define ROTA_ADETI 8
#define dalgasalHiz 8
int sonKullanilanDonumNoktasi = -1;
int led = 0;
int yol = 0;
bool yon = true;
int rotalar[ROTA_ADETI][2];
int yollar[YOL_ADETI][2] =
{
  {0, 36},
  {36, 79},
  {79, 83},
  {83, 116},
  {116, 143},
  {143, 160},
  {160, 206},
  {206, 218},
  {218, 234},
  {234, 289}
};

int kesisimNoktalari[][2] =
{
  {36, 116},
  {143, 160},
  {79, 206},
  {83, 218},
  {234, 289}
};
void random_moving_light_setup() {

}
void random_moving_light_loop() {

  rotaIslemleri();
  ledYurut(yollar[yol][yon], yollar[yol][!yon]);

  fadeToBlackBy( leds, NUM_LEDS, 1);
  FastLED.show();
}

void ledYurut(int baslangic , int bitis ) {
  bool _yon = baslangic < bitis;
  /*Serial.print("LED : ");
    Serial.print(led);
    Serial.print(" || Baslangic : ");
    Serial.print(_yon ? baslangic : bitis);
    Serial.print(" || Bitis : ");
    Serial.println(!_yon ? baslangic : bitis);*/
  led = beatsin16(dalgasalHiz, _yon ? baslangic : bitis, !_yon ? baslangic : bitis , _yon ? 0 : 60000 / dalgasalHiz , 0);
  //led = !_yon ? baslangic : bitis;
  leds[led].setRGB(random(100), random(100), random(100));
  Serial.println(led);
}

















bool donumNoktasiTekrarlaniyorMu() {

  if ( sonKullanilanDonumNoktasi != led ) {
    sonKullanilanDonumNoktasi = led;

    for ( int i = 0 ; i < ARRAY_SIZE(kesisimNoktalari) ; i++ )
      for ( int j = 0 ; j < ARRAY_SIZE(kesisimNoktalari[0]) ; j++ )
        if ( sonKullanilanDonumNoktasi == kesisimNoktalari[i][j] )
          return yolunSonuMu(kesisimNoktalari[i][!j]);



  }

  return false;

}


void rotaIslemleri() {

  if ( !yolunSonuMu(led) )
    return;

  simdikiZaman = millis();
  if ( simdikiZaman - rotaHesaplamaZamani < 2000 )
    return;

  rotaHesaplamaZamani = simdikiZaman;

  /*if ( donumNoktasiTekrarlaniyorMu() ) {
    return;
    }*/

  rotalariTemizle();
  rotalariOlustur(led);
  kesisimRotalariOlustur(led);
  rastgeleRotaSec();
}
void rotalariTemizle() {
  for ( int i = 0 ; i < ARRAY_SIZE(rotalar) ; i++ )
    rotalar[i][0] = -1;
}
void rotalariOlustur(int ledNo) {
  for ( int i = 0 ; i < ARRAY_SIZE(yollar) ; i++ ) {
    for ( int j = 0 ; j < ARRAY_SIZE(yollar[0]) ; j++ ) {
      if ( yollar[i][j] == ledNo ) {
        rotaEkle(i, j);
      }
    }
  }
}
void kesisimRotalariOlustur(int ledNo) {
  for ( int i = 0 ; i < ARRAY_SIZE(kesisimNoktalari) ; i++ )
    for ( int j = 0 ; j < ARRAY_SIZE(kesisimNoktalari[0]) ; j++ )
      if ( ledNo == kesisimNoktalari[i][j] )
        rotalariOlustur(kesisimNoktalari[i][!j]);

}
void rotaEkle(int yol , bool yon ) {
  for ( int i = 0 ; i < ARRAY_SIZE(rotalar) ; i++ ) {
    if ( rotalar[i][0] == -1 ) {
      rotalar[i][0] = yol;
      rotalar[i][1] = yon;
      /*
        Serial.print("yol : ");
        Serial.print(yol);
        Serial.print(" - ");
        Serial.print(yon);
        Serial.println(" : yon");
      */
      break;
    }
  }
}
void rastgeleRotaSec() {
  byte rotaAdeti = 0;
  for ( int i = 0 ; i < ARRAY_SIZE(rotalar) ; i++ ) {
    if ( rotalar[i][0] == -1 )
      break;

    /*
      Serial.print(i);
      Serial.print(". rota - ");
      Serial.print(rotalar[i][0]);
      Serial.print(" : ");
      Serial.println(rotalar[i][1]);
    */

    rotaAdeti++;
  }

  byte yeniRota = random(rotaAdeti);
  yol = rotalar[yeniRota][0];
  yon = rotalar[yeniRota][1];

}

bool yolunSonuMu(int pos) {

  for ( int i = 0 ; i < ARRAY_SIZE(yollar) ; i++ ) {
    for ( int j = 0 ; j < ARRAY_SIZE(yollar[0]) ; j++ ) {
      if ( yollar[i][j] == pos ) {
        return true;
      }
    }
  }
  return false;
}
