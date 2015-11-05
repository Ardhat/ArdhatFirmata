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
      if (bitRead( PORTC, 3)) {   // if Pi power is turned off, turn it on, and status LED too
        pinMode(nPIPWR, OUTPUT);
        digitalWrite(nPIPWR, LOW);
        digitalWrite(LED, HIGH);
        led.Set(Idle); 
      } else {                    // else turn off PI and pulse LED
        digitalWrite(nPIPWR, HIGH);
        pinMode(nPIPWR, INPUT_PULLUP);
        led.Set(PulseStart);
      }
    button.Set(Open); //update state machine
    }
  }
}
