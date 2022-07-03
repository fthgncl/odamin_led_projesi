bool buttonState[2];
void button_control() {
  buttonState[0] = digitalRead(buttonPIN) == 1;
  if ( buttonState[0] && !buttonState[1] ) {
    buttonPressed();
  }
  buttonState[1] = buttonState[0];
}
void buttonPressed() {
  runByTime = !runByTime;
  blynkUpdateDashBoard();
}
