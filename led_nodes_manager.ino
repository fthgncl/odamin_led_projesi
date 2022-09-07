#define INT16_MAX 32767
void rotalariHesapla(uint16_t yol[][2] , byte yolSize , uint16_t kesisimNoktalari[][2] , byte kesisimNoktalariSize , uint16_t sayi, uint16_t cikti[][2] , byte ciktiSize) {
  if (  dugumNoktasiMi(yol , yolSize , sayi) ) {
    dugumNoktasiHattiniEkle(yol , yolSize , sayi, cikti , ciktiSize);
    dugumNoktasiKesisimHatlariniEkle(yol , yolSize , kesisimNoktalari , kesisimNoktalariSize , sayi, cikti , ciktiSize);
  }
  else
  {
    uint16_t ucNoktalar[2];
    enYakinUclariBul(yol , yolSize , sayi , ucNoktalar);
    arrayEklemeYap(cikti, ciktiSize, ucNoktalar);
    yollariYazdir(cikti, ciktiSize);
  }
}
void dugumNoktasiHattiniEkle(uint16_t yol[][2] , byte yolSize , uint16_t sayi, uint16_t cikti[][2] , byte ciktiSize) {
  for ( byte i = 0 ; i < yolSize ; i++ )
    for ( byte j = 0 ; j < 2 ; j++ )
      if ( yol[i][j] == sayi ) {
        uint16_t eklenenSayi[2] = { yol[i][j] , yol[i][!j] };
        arrayEklemeYap(cikti, ciktiSize, eklenenSayi );
        j = 2;
      }
}
void dugumNoktasiKesisimHatlariniEkle(uint16_t yol[][2] , byte yolSize , uint16_t kesisimNoktalari[][2] , byte kesisimNoktalariSize , uint16_t sayi, uint16_t cikti[][2] , byte ciktiSize) {
  for ( byte i = 0 ; i < kesisimNoktalariSize ; i++ )
    for ( byte j = 0 ; j < 2 ; j++ )
      if ( kesisimNoktalari[i][j] == sayi )
        dugumNoktasiHattiniEkle(yol , yolSize , kesisimNoktalari[i][!j], cikti , ciktiSize);
}
void arrayEklemeYap(uint16_t arr[][2], byte arrSize, uint16_t eklenecekVeri[2]) {
  for ( byte i = 0 ; i < arrSize ; i++ )
    if ( arr[i][0] + arr[i][1] == 0 ) {
      arr[i][0] = eklenecekVeri[0];
      arr[i][1] = eklenecekVeri[1];
      break;
    }
}
void enYakinUclariBul(uint16_t yol[][2] , byte yolSize , uint16_t sayi, uint16_t uclar[2]) {
  int16_t enYakinMesafe[2];
  enYakinMesafe[0] = INT16_MAX;
  enYakinMesafe[1] = INT16_MAX;

  int16_t mesafe;
  for (byte i = 0 ; i < yolSize ; i++)
    for ( byte j = 0 ; j < 2 ; j++ ) {

      mesafe = yol[i][j] - sayi;

      if ( abs(mesafe) < abs(enYakinMesafe[1]) && mesafe != enYakinMesafe[0] )
        enYakinMesafe[1] = mesafe;


      if ( abs(enYakinMesafe[1]) < abs(enYakinMesafe[0]) ) {
        mesafe = enYakinMesafe[0];
        enYakinMesafe[0] = enYakinMesafe[1];
        enYakinMesafe[1] = mesafe;
      }
    }

  uclar[0] = sayi + enYakinMesafe[0];
  uclar[1] = sayi + enYakinMesafe[1];
}


bool dugumNoktasiMi(uint16_t yol[][2] , byte yolSize , uint16_t sayi) {
  for (byte i = 0 ; i < yolSize ; i++)
    if ( yol[i][0] == sayi || yol[i][1] == sayi )
      return true;

  return false;
}
void yollariYazdir(uint16_t arr[][2] , byte arrSize) {
  for (byte i = 0 ; i < arrSize ; i++) {
    Serial.print(i);
    Serial.print(" | ");
    Serial.print(arr[i][0]);
    Serial.print(" - ");
    Serial.println(arr[i][1]);
  }
}
