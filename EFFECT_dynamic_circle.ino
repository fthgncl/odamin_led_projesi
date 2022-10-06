#define avizeLedBaslangic 235
#define avizeLedBitis 289
byte cemberSayaci = 0;
void dynamic_circle_setup(byte effectID) {

}
void dynamic_circle_loop()
{
  EVERY_N_MILLISECONDS(10) {
    byte hue = 0;
    for ( int i = avizeLedBaslangic , j = 0 ; i <= avizeLedBitis ;  i++ , j++ , hue = cemberSayaci + (j * 360 / (avizeLedBitis - avizeLedBaslangic))) {
      leds[i] = CHSV(hue, 255, 255);
    }
    cemberSayaci++;
  }
}
