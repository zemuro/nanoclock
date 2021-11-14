/*
the nanoclock
an Arduino master clock

partly based on 'Arduino MIDI clock with tap tempo' by DieterVDW (https://github.com/DieterVDW/arduino-midi-clock)

(C) Ruslan Mazavin, 2021, CC-BY 3.0
*/

#include <Arduino.h>
#include <TimerOne.h>
#include "multipots.h"
#include "displays.h"
#include <GyverTM1637.h>

using namespace Nanoclock;
                              //  Target board selection
                              //  Uncomment the board you're compiling for
//#define ATTINY88            //  MH-Tiny ATtiny88 Micro
#define ARDUINOUNO            //  Standard Arduino Uno
//#define OLED                //  Arduino Uno with a fancy OLED display
//#define MIDI                //  Use MIDI clock
//#define TAPBPM              //  TAP TEMPO button
//#define BLINKERS            //  1 blinking LED for master clock, 3 LEDs for auxillary channels
//#define BPM_ENCODER         //  would be logical to change tempo with an encoder (two input pins)
//#define RATIOS_ENCODERS     //  change AUX dividers with encoders (six input pins)


#ifdef OLED          //  OLED display for graphical menus, replaces BPM indicator
  #include <Adafruit_SSD1306.h> //  for future advanced model with multiple options
  #include <Adafruit_GFX.h>     //  like MIDI CLOCK sync options, trigger/gate sync
  #include <SPI.h>              //  configuring PPQN and whatnot
  #include <Wire.h>             //
  #define OLED_DC     8       //
  #define OLED_CS     10        //  SPI OLED Display 128x64, SSD1306, SPI
  #define OLED_RESET  9         //  We're using the hardware SPI
  #define SCREEN_WIDTH 128      // Pin 11 (MOSI) to D1, Pin 13 (SCK) to D0
  #define SCREEN_HEIGHT 64

  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);
#endif

//================================================== Muxed potentiometers

//#define PW                    //uncomment for PULSE WIDTH inputs
#ifdef PW
#endif

//#define SWING                 //uncomment for SWING
#ifdef SWING
#define MAIN_SWING_POT 
#define AUX1_SWING_POT 
#define AUX2_SWING_POT 
#define AUX3_SWING_POT
#endif

//================================================== Input pins (buttons)

#define RESET_PIN 1             //  RESET button and trigger input  (diode "or" gate)
#define RUN_PIN 2               //  RUN/STOP button and trigger input (diode "or" gate)

#define ADC_PIN 15

/*                              //  Reserved for future advanced mode
#define MODE_MINUS_PIN 3        //  EXTERNAL SYNC MODE -
#define MODE_PLUS_PIN 4         //  EXTERNAL SYNC MODE +
*/

//=================================================== Encoders

#ifdef BPM_ENCODER
#define ENC_BPM_PIN1
#define ENC_BPM_PIN2
#endif

#ifdef RATIOS_ENCODERS
#define ENC_AUX1_PIN1
#define ENC_AUX1_PIN2
#define ENC_AUX2_PIN1
#define ENC_AUX2_PIN2
#define ENC_AUX3_PIN1
#define ENC_AUX3_PIN2
#endif  

/*
#define RESET_OUT_PIN 123       //  forward RESET and RUN signals (may be done electrically)  
#define RUN_OUT_PIN 12          //
*/

#ifdef TAPBPM
#define TAP_PIN 3               // Tap tempo button
#endif

//===================================================  Output pins

#define OUT_MAIN_PIN 4          // Main out - 4th? 8th? 16th? we need a divider somewhere!
#define OUT1_PIN 5              // Auxillary outputs
#define OUT2_PIN 6
#define OUT3_PIN 7

//==================================================== MUXed pots
#ifdef ARDUINOUNO
#define MUX_S0  2   // Select Arduino pins 2 to 5 for addressing individual pots
#define MUX_S1  3   // 
#define MUX_S2  4
#define MUX_S3  5
#define ANALOG_INPUT_PIN  A3  // Potentiometer value
#endif

#ifdef ATTINY88
#define MUX_S0  3
#define MUX_S1  4
#define MUX_S2  5 
#define MUX_S3  6
#define ANALOG_INPUT_PIN A3
#endif

#ifdef ARDUINOUNO
#define MAIN_DIO 5
#define MAIN_CL 6
#define AUX1_DIO 5
#define AUX1_CL 6
#define AUX2_DIO 5
#define AUX2_CL 6
#define AUX3_DIO 5
#define AUX3_CL 6
#endif

#ifdef ATTINY88
#define MAIN_DIO 5
#define MAIN_CL 6
#define AUX1_DIO 5
#define AUX1_CL 6
#define AUX2_DIO 5
#define AUX2_CL 6
#define AUX3_DIO 5
#define AUX3_CL 6
#endif

//=================================================== Multiplexing 7-segment LEDs




void setup() {
  
  MultiplexedPots pots(MUX_S0, MUX_S1, MUX_S2, MUX_S3, ANALOG_INPUT_PIN);
  DisplaysCombo displays(MAIN_DIO, MAIN_CL, AUX1_DIO, AUX1_CL, AUX2_DIO, AUX2_CL, AUX3_DIO, AUX3_CL);
  
  displays.clear();   //

#ifdef MIDI
  Serial1.begin(31250);
#endif

#ifdef OLED
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
   // Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
#endif

}

void loop() {
  long now = micros();
  /*
   check the RUN switch
   check the interface pins

*/
}