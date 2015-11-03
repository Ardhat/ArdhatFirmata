/*
Change brightness of LED linearly to Human eye
32 step brightness using 8 bit PWM of Arduino
brightness step 24 should be twice bright than step 12 to your eye.
*/



#include <avr/pgmspace.h>
#define CIELPWM(a) (pgm_read_byte_near(CIEL8 + a)) // CIE Lightness loopup table function

/*
5 bit CIE Lightness to 8 bit PWM conversion
L* = 116(Y/Yn)^1/3 - 16 , Y/Yn > 0.008856
L* = 903.3(Y/Yn), Y/Yn <= 0.008856
*/

const char CIEL8[] PROGMEM = {
  0,    0,    0,    1,    2,    3,    4,    9,    12,
  15,    18,    22,    27,    32,    38,    44,    51,    58,
  67,    76,    86,    96,    108,    120,    134,    148,    163,
  180,    197,    216,    235,    255
};

int brightness = 1;
int fadeAmount = 1;
int stepTime = 50;


State Idle() {
  }

State PulseStart(){
      brightness = 0;    // initial brightness of LED
      fadeAmount = 1;
      led.Set(Pulse);
}

State Pulse()  {
  if (led.Timeout(stepTime))
  {   analogWrite(LED, CIELPWM(brightness));
      brightness = brightness + fadeAmount;
      // reverse the direction of the fading at the ends of the fade:
      if (brightness == 0 || brightness == 31) fadeAmount = -fadeAmount ;
      led.Set(Pulse);   // renter state to another step time
  }
}

State BlinkOn(){
  digitalWrite(LED, HIGH);// sets the LED on
  if(led.Timeout(400)) led.Set(BlinkOff);
}


State BlinkOff(){
  digitalWrite(LED, LOW);   // sets the LED on
  if(led.Timeout(400)) led.Set(BlinkOn);
}


