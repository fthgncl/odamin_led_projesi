#define avizeLedBaslangic 233
#define avizeLedBitis 289
int const avizeHalkasiLedAdeti = abs(avizeLedBaslangic - avizeLedBitis) + 1;
int harAvizeSayac = 0;

#define harAvizeParlaklik 120
#define maxIsikYolu 6
int isikYolu[maxIsikYolu][avizeHalkasiLedAdeti];
int yolRenkleri[maxIsikYolu][3];
bool ledAraliktaMi(int ledNo, int baslangic, int bitis) {
  if ( baslangic > bitis ) {
    if ( ledNo <= bitis || ledNo >= baslangic )
      return true;
    else
      return false;
  }
  else
  {
    if ( baslangic <= ledNo && ledNo <= bitis )
      return true;
    else
      return false;
  }
}
int ledNoKontrol(int ledID = avizeLedBaslangic) {
  while ( ledID > avizeLedBitis )
    ledID -=  avizeLedBitis - avizeLedBaslangic + 1;

  while ( ledID < avizeLedBaslangic )
    ledID +=  avizeLedBitis - avizeLedBaslangic + 1;

  return ledID;
}
int bosYolBul() {
  for ( int i = 0 ; i < ARRAY_SIZE(isikYolu) ; i++) {
    if ( isikYolu[i][0] <= 0 ) {
      return i;
    }
  }
  return -1;
}
void isikYoluOlustur(int baslangic, int bitis, int adimSayisi ,  byte hiz) {
  int bosYol = bosYolBul(); // Bos bir düngü bul

  if ( bosYol == -1 ) {     // Eğer yoksa geri dön
    return;
  }

  int aralik = (abs(baslangic - bitis) / adimSayisi) + 1;
  int yon = bitis > baslangic ? 1 : -1;
  isikYolu[bosYol][0] = hiz;
  for ( int i = 0 ; i < aralik ; i++  ) {
    isikYolu[bosYol][i + 1] = ledNoKontrol(baslangic + (i * adimSayisi * yon));
  }



}
void isikYollariniTemizle() {
  for ( int i = 0 ; i < ARRAY_SIZE(isikYolu) ; i++ )
    for ( int j = 0 ; j < ARRAY_SIZE(isikYolu[0]) ; j++ )
      isikYolu[i][j] = 0;
}
void halkaOlustur(int parcaAdeti) {
  int parcaUzunlugu = avizeHalkasiLedAdeti / parcaAdeti;
  for ( int i = 0 ; i < parcaAdeti ; i ++ ) {
    isikYoluOlustur(i * parcaUzunlugu, (i + 1)*parcaUzunlugu - 1 , 1, 1);
  }
}
void rastgeleRenkOlustur() {
  for ( int i = 0 ; i < ARRAY_SIZE(yolRenkleri) ; i++ ) {
    yolRenkleri[i][0] = random(harAvizeParlaklik);
    yolRenkleri[i][1] = random(harAvizeParlaklik);
    yolRenkleri[i][2] = random(harAvizeParlaklik);
  }

}
void dynamic_circle_loop() {

  if ( harAvizeSayac == 0 ) {
    isikYollariniTemizle();
    rastgeleRenkOlustur();
    halkaOlustur(random(1,ARRAY_SIZE(isikYolu)));
  }
  if ( harAvizeSayac >= 1 && harAvizeSayac < ARRAY_SIZE(isikYolu[0]) - 1 ) {
    isikYolariniYurut();
  }

  harAvizeSayac++;

  if (harAvizeSayac >= 500)
    harAvizeSayac = 0;

}
void isikYolariniYurut() {

  int ledNums[maxIsikYolu];
  for ( int i = 0 ; i < ARRAY_SIZE(isikYolu) ; i++ ) {
    ledNums[i] = isikYolu[i][harAvizeSayac + 1];
    if (ledNums[i] != 0) {
      leds[ledNums[i]].r = yolRenkleri[i][0];
      leds[ledNums[i]].g = yolRenkleri[i][1];
      leds[ledNums[i]].b = yolRenkleri[i][2];
    }
  }
}
