#include <Arduino.h>             // Arduino core
#include <interface.h>
#include <clock.h>
#include <taptempo.h>
#include <TimerOne.h>

//#define ATTINY88              //  MH-Tiny ATtiny88 Micro
#define ARDUINO_UNO             //  Standard Arduino Uno
//#define ARDUINOPROMICRO       //  Arduino 

#define MIN_BPM 30
#define MAX_BPM 260
#define DEFAULT_BPM 100


//#define POT_TEMPO
#ifdef POT_TEMPO
#define TEMPO_POT 3
#endif


#ifdef ATTINY88
#define MUX_S0  3
#define MUX_S1  4
#define MUX_S2  5 
#define MUX_S3  6
#define ANALOG_INPUT_PIN A3
#define MAIN_DIO 5
#define MAIN_CL 6
#define AUX1_DIO 5
#define AUX1_CL 6
#define AUX2_DIO 5
#define AUX2_CL 6
#define AUX3_DIO 5
#define AUX3_CL 6
#endif

#ifdef ARDUINO_UNO

    #define BUTTONS_2017_CLK    11     // won't do, need to use 2017 arrangement (2 pins)
    #define BUTTONS_2017_KEY    12
    #define BUTTONS_2017_RST    13

    #define SINGLE_DISPLAY
    #ifdef SINGLE_DISPLAY
        #define DISPLAY_DIO 9      // 4 x 4x7-segment displays (8 digital pins)
        #define DISPLAY_CL 10       // actually a single display could be used (function buttons select a visible parameter, changeable with an encoder)
    #endif

    #define ENC_PIN_A   1       // encoder pins (2 digital pins)
    #define ENC_PIN_B   8

    // Outputs (4 pins)
    
    const uint8_t OUT_MAIN_PIN = 4;
    const uint8_t OUT1_PIN = 5;
    const uint8_t OUT2_PIN = 6;
    const uint8_t OUT3_PIN = 7;
 
    
    #define TAP_TEMPO
        #ifdef  TAP_TEMPO
        #define TAP_PIN 3               // Tap tempo button (1 digital pin) 
        #define TAP_POLARITY LOW

    #endif
                            // 15 to 11 pins required
#endif

enum Modes{
        KEY_RUN       = 0,
        KEY_RESET     = 1,
        KEY_PW        = 2,
        KEY_SWING     = 3,
        AUX1_DIVISOR  = 4,
        AUX1_PW       = 5,
        AUX1_SWING    = 6,
        AUX1_DELAY    = 7,
        AUX2_DIVISOR  = 8,
        AUX2_PW       = 9,
        AUX2_SWING    = 10,
        AUX2_DELAY    = 11,
        AUX3_DIVISOR  = 12,
        AUX3_PW       = 13,
        AUX3_SWING    = 14,
        AUX3_DELAY    = 15,
        MAIN_DIVISOR  = 16,
        MAIN_TEMPO    = 17,
        OPTION_2      = 18,
        COUNTER       = 19
    };

//static uint8_t bpm;
//static uint8_t encoderMode;
//static uint8_t main_PW;
bool encoderRead;
//static uint8_t state;
static volatile uint8_t currentMode;
// static volatile long now;

// Encoder modes

//}
#define ENCODER_PERIOD 500      //  ms
//}
//using namespace Nanoclock;
PhysicalInterface physicalInterface(16, BUTTONS_2017_CLK, BUTTONS_2017_KEY, BUTTONS_2017_RST, ENC_PIN_A, ENC_PIN_B, DISPLAY_CL, DISPLAY_DIO); 
TapTempo tapButton(TAP_PIN, MIN_BPM, MAX_BPM, TAP_POLARITY);


const long DEFAULT_TEMPO = 1000;
Clock clock(OUT_MAIN_PIN, OUT1_PIN, OUT2_PIN, OUT3_PIN);   // tick tock q

void tick()
{
    if (clock.running) {
        clock.tick();
    }
}


void setup()
{

    Timer1.initialize(clock.intervalMicroseconds);                    // value is 1000000 by default
    Timer1.setPeriod(clock.calculateIntervalMicroSecs(DEFAULT_TEMPO));
    Timer1.attachInterrupt(tick);
}

void loop()
{
}

