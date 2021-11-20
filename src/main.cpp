/*
the nanoclock
an Arduino master clock

partly based on 'Arduino MIDI clock with tap tempo' by DieterVDW (https://github.com/DieterVDW/arduino-midi-clock)

(C) Ruslan Mazavin, 2021, CC-BY 3.0
*/

#include <Arduino.h>
#include "main.h"



using namespace Nanoclock;

void setup() {
  
  //DisplaysCombo displays(MAIN_DIO, MAIN_CL, AUX1_DIO, AUX1_CL, AUX2_DIO, AUX2_CL, AUX3_DIO, AUX3_CL);
  TapButton tapbutton(TAP_PIN, MIN_BPM, MAX_BPM, MINIMUM_TAPS, TAP_POLARITY, EXIT_MARGIN);
  Clock clock();
  displays.clear();  
  //Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);
  //Buttons buttons();
};

void loop() {

  // check button pressed (external interrupt mb)
  // is there anything new? (last presed button priority)
  // the button sets what parameter is displayed and edited with the encoder
  // if 
  // 
};

void updateBpm(){

};