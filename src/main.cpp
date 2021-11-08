/*
the nanoclock
an Arduino master clock

partly based on 'Arduino MIDI clock with tap tempo' by DieterVDW (https://github.com/DieterVDW/arduino-midi-clock)

(C) Ruslan Mazavin, 2021, CC-BY 3.0
*/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimerOne.h>

//  SPI OLED Display 128x64, SSD1306 ibterface

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_DC     8
#define OLED_CS     10
#define OLED_RESET  9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);


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

// omg we need some serious MUX here!

void drawInterface();

void setup() {

#ifdef MIDI
  Serial1.begin(31250);
#endif

  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
   // Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  long now = micros();
  /*
   check the RUN switch
   check the interface pins

*/
}