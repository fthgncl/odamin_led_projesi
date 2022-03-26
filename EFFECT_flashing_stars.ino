byte parlayacakYildizlar[10][2];
#define parlaklikDegeri 150
int yildizPariltisiSayaci = 0;
byte yildizPariltisiGiris = 0;


void yildizPariltisiOnAyar() {
  Serial.println("Yildiz Pariltisi Giriş Yapıldı");
  int led;
  for ( int i = 0 ; i < ARRAY_SIZE(parlayacakYildizlar) ; i ++ ) {
    flashingStars();
    led = parlayacakYildizlar[i][0];
    for (int j = 0; j < 3; j++) {
      leds[led][j] = int(i * (2 * parlaklikDegeri / ARRAY_SIZE(parlayacakYildizlar)));
    }
  }

  leds[0].setRGB(0, 0, 0);
}


void flashingStars() {
  if ( yildizPariltisiGiris == 1 ) {
    yildizPariltisiGiris = 2;
    yildizPariltisiOnAyar();
  }
  else

    isikSiddetiniAyarla();

  int katman = bostaKatmanBul();
  if ( katman == -1 )
    return;


  parlayacakYildizlar[katman][1] = 1;

  int led = 0;
  while ( !led ) {
    led = bostaLedBul(0, NUM_LEDS);
    parlayacakYildizlar[katman][0] = led;
  }
}

void isikSiddetiniAyarla() {

  if ( yildizPariltisiSayaci >= ARRAY_SIZE(parlayacakYildizlar ) - 1 )
    yildizPariltisiSayaci = 0;
  else yildizPariltisiSayaci++;

  int katman = yildizPariltisiSayaci;
  int led = parlayacakYildizlar[katman][0];

  for (int i = 0; i < 3; i++) {
    leds[led][i] += 1 * (parlayacakYildizlar[katman][1] == 1) ? 1 : -1;
  }

  if ( leds[led].r >= parlaklikDegeri || leds[led].g >= parlaklikDegeri || leds[led].b >= parlaklikDegeri )
    parlayacakYildizlar[katman][1] = 0;
  else if ( leds[led].r <= 0 && leds[led].g <= 0 && leds[led].b <= 0 ) {
    parlayacakYildizlar[katman][0] = 0;
  }
}
int bostaLedBul(int baslangic, int bitis) {
  int ledNo = random(baslangic, bitis);

  for ( int i = 0 ; i < ARRAY_SIZE(parlayacakYildizlar) ; i ++ ) {
    if ( parlayacakYildizlar[i][0] == ledNo ) {
      ledNo = 0;
      break;
    }
  }

  return ledNo;
}
int bostaKatmanBul() {
  int katman = -1;
  for ( int i = 0 ; i < ARRAY_SIZE(parlayacakYildizlar) ; i ++ ) {
    if ( parlayacakYildizlar[i][0] == 0 ) {
      katman = i;
      parlayacakYildizlar[i][1] = 1;
      break;
    }
  }
  return katman;
}
