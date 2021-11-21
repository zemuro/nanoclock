/*
the nanoclock
an Arduino master clock

partly based on 'Arduino MIDI clock with tap tempo' by DieterVDW (https://github.com/DieterVDW/arduino-midi-clock)

(C) Ruslan Mazavin, 2021, CC-BY 3.0
*/

#include <Arduino.h>
#include "main.h"

using namespace Nanoclock;

// Firstly, let's instantiate the objects

MD_UISwitch_4017KM buttons(16, BUTTONS_2017_CLK, BUTTONS_2017_KEY, BUTTONS_2017_RST); // the button matrix
TapTempo tapbutton(TAP_PIN, MIN_BPM, MAX_BPM, TAP_POLARITY);                          // the tap tempo/ALT button
Clock clock;                                                                          // the clock (parameters, timers, math and outputs)
MD_REncoder encoder = MD_REncoder(ENC_PIN_A, ENC_PIN_B);                              // the encoder
GyverTM1637 display(MAIN_DISPLAY_CL, MAIN_DISPLAY_DIO);                               // well, it's kinda self-descriptory

// and initialize the variables

void setup() {
  bpm = DEFAULT_BPM;
  buttons.begin();
  buttons.enableDoublePress (false);
  buttons.enableLongPress (false);
  buttons.enableRepeat (false);
  buttons.enableRepeatResult (false);

  encoder.begin();
  encoder.setPeriod(ENCODER_PERIOD);
  clock.initialize (bpm);
};

void loop() {
  MD_UISwitch::keyResult_t key = buttons.read();// let's check out these buttons (will move this code to some class later)
  if (key != MD_UISwitch::KEY_NULL)             // if some button state changed..
    if (key == MD_UISwitch::KEY_UP)             // oh, a depressed button
      {
        encoderMode = MAIN_TEMPO;               // return to the default mode
      }
      else{                                     // well, some key was pressed
        uint8_t keyNumber = buttons.getKey();   // let's find out what button
        switch (keyNumber){                     // and select a parameter 
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
  
        uint8_t encoderData = encoder.read();                           // returns zero if nothing happened, DIR_CW or DIR_CCW for clockwise or counterclockwise rotation
        if(encoderData){                                                // not zero?
          uint8_t encoderSpeed = encoder.speed();                       // returns encoder speed in clicks per second, usually in the range 0..59
          char changeValue = adaptiveChange(encoderData, encoderSpeed); // returns increment or decrement value (SIGNED)
          switch (encoderMode){                                         // now we find out what parameter gets changed (determined by scanning the keyboard)
            case MAIN_TEMPO: {
              clock.changeParameter (MAIN, TEMPO, changeValue);         // and now we politely ask the clock to change the tempo etc
              break;
            }
            case MAIN_PW: {
              clock.changeParameter (MAIN, PW, changeValue);            // All this will be encapsulated in some class, when I've figured out which exactly
              break;                                                    // Maybe class Interface
            }                                                           //
            case MAIN_SWING: {                                          // interface.parseButtons() or interface.checkEncoder()
              clock.changeParameter (MAIN, SWING, changeValue);         // 
              break;                                                    //
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
  
  // and now we show the value
  // omg here goes the display class
  // or actually che clock... like clock.refreshDisplay() or something

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