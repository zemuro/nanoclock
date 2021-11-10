#include <Arduino.h>
#include "multipots.h"

using namespace Nanoclock;

//=================================================== Multiplexing potentiometers with 4067
 
/*  Interfacing analog potentiometers
    Arduino Uno has only 6 ADCs, ATTiny88 has 8
    We'll use 4067 multiplexer for analog, so it takes:
        1 ADC pin
        4 digital pins for addressing
    !EN shorted to ground
*/

  MultiplexedPots::MultiplexedPots(int a0, int a1, int a2, int a3, int adcPin){ // the class constructor
    pinMode (a0, OUTPUT); // setting pins for OUTPUT
    pinMode (a1, OUTPUT); // will address the MUX
    pinMode (a2, OUTPUT);                                           
    pinMode (a3, OUTPUT);
    _a0 = a0; // initialising values
    _a1 = a1;
    _a2 = a2;
    _a3 = a3;
    _adcPin = adcPin;
  }

  void MultiplexedPots::setChannel(int channel)
{
  digitalWrite(_a0, channel_bits[channel][0]);
  digitalWrite(_a1, channel_bits[channel][1]);
  digitalWrite(_a2, channel_bits[channel][2]);
  digitalWrite(_a3, channel_bits[channel][3]);
}

int MultiplexedPots::potValue(int chan){
  setChannel(chan);
  return analogRead(_adcPin);
}