#define DEBOUNCE 250


State Open()  {

  if (button.Timeout(DEBOUNCE)) { //wait for debounce
    if (map(analogRead(NAV), 0, 1023, 0, 12) == 0) {
      button.Set(Pushed);
    }
  }
}


State Pushed()  {

  if (button.Timeout(DEBOUNCE)) { //wait for debounce

    if (map(analogRead(NAV), 0, 1023, 0, 12) > 3) {
      button.Set(Open);

      if (bitRead( PORTC, 3)) {    // if Pi power is turned off, turn it on and pulse LED
        pinMode(nPIPWR, OUTPUT);
        digitalWrite(nPIPWR, LOW);
        led.Set(PulseStart);
        
      } else {           // else turn off PI and LED
        digitalWrite(nPIPWR, HIGH);
        pinMode(nPIPWR, INPUT_PULLUP);
        digitalWrite(LED, LOW);
        led.Set(Idle);
        
      }
    }
  }
}
