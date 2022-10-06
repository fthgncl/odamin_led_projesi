uint16_t yollar[][2] =
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

uint16_t kesisimNoktalari[][2] =
{
  {36, 116},
  {143, 160},
  {79, 206},
  {83, 218},
  {234, 289}
};

uint16_t hareketliIsik[3];
byte renk[3];

void rastgele_yol_setup(byte EffectID) {


}

void rastgele_yol_loop() {
  EVERY_N_MILLISECONDS(100) {

    if ( dugumNoktasiMi(yollar, ARRAY_SIZE(yollar), hareketliIsik[0] )) {
      for ( byte i = 0 ; i < 3 ; i ++ )
        renk[i] = random(255);
      
      uint16_t cikti[10][2];
      rotalariHesapla(yollar, ARRAY_SIZE(yollar), kesisimNoktalari , ARRAY_SIZE(kesisimNoktalari) , hareketliIsik[0] , cikti , ARRAY_SIZE(cikti));

      for (byte i = 0 ; i < ARRAY_SIZE(cikti) ; i++) {
        if ( cikti[i][0] == 0 && cikti[i][1] == 0 ) {
          byte rastgeleSayi = random(i - 1);
          hareketliIsik[1] = cikti[rastgeleSayi][0];
          hareketliIsik[2] = cikti[rastgeleSayi][1];
          break;
        }
      }
    }

    hareketliIsik[0] += hareketliIsik[1] < hareketliIsik[2] ? 1 : -1;
    fadeToBlackBy( leds, NUM_LEDS, 10);
    leds[hareketliIsik[0]].setRGB(renk[0],renk[1],renk[2]);


  }
}
