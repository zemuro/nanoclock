/*
the nanoclock
an Arduino master clock

partly based on 'Arduino MIDI clock with tap tempo' by DieterVDW (https://github.com/DieterVDW/arduino-midi-clock)

(C) Ruslan Mazavin, 2021, CC-BY 3.0
*/

#include <Arduino.h>
#include <TimerOne.h>
                              //  Target board selection
                              //  Uncomment the board you're compiling for
//#define ATTINY88            //  MH-Tiny ATtiny88 Micro
#define ARDUINOUNO            //  Standard Arduino Uno
//#define ARDUINOUNO_OLED     // Arduino Uno with a fancy OLED display


#ifdef ARDUINOUNO_OLED
  #include <Adafruit_SSD1306.h>
  #include <Adafruit_GFX.h>
  #include <SPI.h>
  #include <Wire.h>           
  
  #define OLED_DC     8       // fancy OLED graphics!
  #define OLED_CS     10      //  SPI OLED Display 128x64, SSD1306, SPI
  #define OLED_RESET  9       //  We're using the hardware SPI
  #define SCREEN_WIDTH 128    // Pin 11 (MOSI) to D1, Pin 13 (SCK) to D0
  #define SCREEN_HEIGHT 64

  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);
#endif



// Pins and encoder

#define RESET_IN_PIN 1          // RESET  (a switch and an input - Diode gates)
#define RUN_IN_PIN 2            // RUN/STOP 
#define RESET_OUT_PIN 123       //
#define RUN_OUT_PIN 12          //

#define TAP_PIN 3               // Tap tempo button

#define OUT_MAIN_PIN 4          // Main out - 4th? 8th? 16th? we need a divider somewhere!

#define OUT1_PIN 5              // Auxillary outputs
#define OUT2_PIN 6
#define OUT3_PIN 7

#define RATIO1_PIN 9             // AUX outs ratios - potentiometers on analog pins
#define RATIO2_PIN 10
#define RATIO3_PIN 11

//  Multiplexing

/*  omg we need some serious MUX here! Interfacing 15 analog potentiometers and 5 digital inputs
    Arduino Uno has only 6 ADCs, ATTiny88 has 8
    We'll use 74HC4047 multiplexer for analog, so it takes:
    
    1 ADC pin
    4 digital pins for addressing specific pots
    !EN shorted to ground

    not bad

*/

class MultiplexedPots {   //  let's have a class!
  
  char a0;                //  adress bus
  char a1;
  char a2;
  char a3;
  char ADCPin;            // well, that's our analog input

  int potValue;           // ADC returns a 10-bit-long measurement value

  public:

  MultiplexedPots(char a0, char a1, char a2, char a3, char adcPin){ // the class constructor
    pinMode (a0, OUTPUT);                                           // theoretically should receive all the pin numbers on init
    pinMode (a1, OUTPUT);                                           // and switch the corresponging pins to output mode
    pinMode (a2, OUTPUT);                                           
    pinMode (a3, OUTPUT);
  }

  int read (char potNumber);                                        // will be implemented somewhere else
};


void setup() {
  MultiplexedPots pots();

#ifdef MIDI
  Serial1.begin(31250);
#endif

#ifdef ARDUINOUNO
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