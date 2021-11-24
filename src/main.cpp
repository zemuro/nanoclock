/*
the nanoclock
an Arduino master clock

partly based on 'Arduino MIDI clock with tap tempo' by DieterVDW (https://github.com/DieterVDW/arduino-midi-clock)

(C) Ruslan Mazavin, 2021, CC-BY 3.0
*/

#include <Arduino.h>
#include "main.h"

//using namespace Nanoclock;

PhysicalInterface physicalInterface(16, BUTTONS_2017_CLK, BUTTONS_2017_KEY, BUTTONS_2017_RST, ENC_PIN_A, ENC_PIN_B, DISPLAY_CL, DISPLAY_DIO); 
TapTempo tapButton(TAP_PIN, MIN_BPM, MAX_BPM, TAP_POLARITY);                // the tap tempo/OPTION button
Clock clock;                                                                // the clock (parameters, timers, math and outputs)

void setup() {
  };

void loop() {
  if (tapButton.check()){
    clock.setBpm(tapButton.newTempo);
  }       

  currentMode = (physicalInterface.checkButtons(tapButton.isHeld)) ? physicalInterface.option : MAIN_TEMPO;
  
  if (physicalInterface.checkEncoder()){
      clock.changeParameter(currentMode, physicalInterface.encoderValue);
  }
  
  physicalInterface.updateDisplay();
  
}