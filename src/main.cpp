/*
the nanoclock
an Arduino master clock

partly based on 'Arduino MIDI clock with tap tempo' by DieterVDW (https://github.com/DieterVDW/arduino-midi-clock)

(C) Ruslan Mazavin, 2021, CC-BY 3.0
*/

#include <Arduino.h>
#include "main.h"



using namespace Nanoclock;
MD_UISwitch_4017KM buttons(16, BUTTONS_2017_CLK, BUTTONS_2017_KEY, BUTTONS_2017_RST);
TapTempo tapbutton(TAP_PIN, MIN_BPM, MAX_BPM, TAP_POLARITY);
Clock clock;
MD_REncoder encoder = MD_REncoder(ENC_PIN_A, ENC_PIN_B);

void setup() {
  
  //DisplaysCombo displays(MAIN_DIO, MAIN_CL, AUX1_DIO, AUX1_CL, AUX2_DIO, AUX2_CL, AUX3_DIO, AUX3_CL);
  buttons.begin();
  buttons.enableDoublePress (false);
  buttons.enableLongPress (false);
  buttons.enableRepeat (false);
  buttons.enableRepeatResult (false);

  encoder.begin();
  encoder.setPeriod(ENCODER_PERIOD);
};

void loop() {
  MD_UISwitch::keyResult_t key = buttons.read();
  if (key != MD_UISwitch::KEY_NULL)             // no key = no input
    if (key == MD_UISwitch::KEY_UP)
      {
        encoderMode = MAIN_TEMPO;
      }
      else{                                     // key presed or repeatedly pressed etc
        uint8_t keyNumber = buttons.getKey();   //let's find out what's pressed and act accordingly
        switch (keyNumber){                     // key index [0-15] - keys defined at nanoclock_configuration.h
          case KEY_RUN: {
            clock.startStop();                  // RUN key pressed
            break;}
          case KEY_RESET: {
            clock.reset();                      // Reset
            break;}
          case KEY_PW: {
            encoderMode = MAIN_PW;
            break;} 
          case KEY_SWING: {
            encoderMode = MAIN_SWING;
            break;}
          case AUX1_DIVISOR:  {
            encoderMode = DIVISOR_1;
            break;}
          case AUX1_PW: {
            encoderMode = PW_1;
            break;}
          case AUX1_SWING: {
            encoderMode = SWING_1;
            break;}
          case AUX1_DELAY: {
            encoderMode = DELAY_1;
            break;}
          case AUX2_DIVISOR:  {
            encoderMode = DIVISOR_2;
            break;}
          case AUX2_PW: {
            encoderMode = PW_2;
            break;}
          case AUX2_SWING:  {
            encoderMode = SWING_2;
            break;}
          case AUX2_DELAY:  {
            encoderMode = DELAY_2;
            break;}
          case AUX3_DIVISOR:  {
            encoderMode = DIVISOR_3;
            break;}
          case AUX3_PW: {
            encoderMode = PW_3;
            break;}
          case AUX3_SWING:  {
            encoderMode = SWING_2;
            break;}
          case AUX3_DELAY:  {
            encoderMode = DELAY_3;
            break;}
          default: break;
        }
        }
  
        uint8_t encoderData = encoder.read();
        if(encoderData){
          uint8_t encoderSpeed = encoder.speed();             //
          char changeValue = adaptiveChange(encoderData, encoderSpeed);
          switch (encoderMode){
            case MAIN_TEMPO: {
              clock.changeParameter (MAIN, TEMPO, changeValue);
              break;
            }
            case MAIN_PW: {
              clock.changeParameter (MAIN, PW, changeValue);
              break;
            }
            case MAIN_SWING: {
              clock.changeParameter (MAIN, SWING, changeValue);
              break;
            }
            case AUX1_SWING: {
              clock.changeParameter (AUX1, SWING, changeValue);
              break;
            }
            case AUX2_SWING: {
              clock.changeParameter (AUX2, SWING, changeValue);
              break;
            }
            case AUX3_SWING: {
              clock.changeParameter (AUX3, SWING, changeValue);
              break;
            }
            case DIVISOR_1: {
              clock.changeParameter (AUX1, DIVISOR, changeValue);
              break;
            }
            case DIVISOR_2: {
              clock.changeParameter (AUX2, DIVISOR, changeValue);              
              break;
            }
            case DIVISOR_3: {
              clock.changeParameter (AUX3, DIVISOR, changeValue);
              break;
            }
            default: break;
          }
        }
};

char adaptiveChange (uint8_t direction, uint8_t speed){
    
  char increment = 1;                          // By default we are changing some value by 1
  
  if (speed > 20){                                // By turning the encoder very fast, we are incrementing/decrementing a value by 4
    increment = 4;
  }
  else if (speed >6){                             // Moderately fast rotation - inc/dec by 2
    increment = 2;
  }
  
  if (direction == DIR_CW) return increment;      // return a positive increment if rotating clockwise
  return -increment;                              // hey, we need a signed type
}