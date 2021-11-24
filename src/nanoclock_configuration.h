/*
            
            The configuration file

*/

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

    #define OUT_MAIN_PIN 4   // Outputs (4 pins)
    #define OUT1_PIN 5
    #define OUT2_PIN 6
    #define OUT3_PIN 7
    
    #define TAP_TEMPO
        #ifdef  TAP_TEMPO
        #define TAP_PIN 3               // Tap tempo button (1 digital pin) 
        #define TAP_POLARITY LOW

    #endif
                            // 15 to 11 pins required
#endif