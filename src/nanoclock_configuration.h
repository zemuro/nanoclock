/*
            
            The configuration file

*/

//#define ATTINY88              //  MH-Tiny ATtiny88 Micro
#define ARDUINO_UNO             //  Standard Arduino Uno
//#define ARDUINOPROMICRO       //  Arduino 

#define MIN_BPM 30
#define MAX_BPM 260


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

        #define KEY_RUN         0
        #define KEY_RESET       1
        #define KEY_PW          2
        #define KEY_SWING       3
        #define AUX1_DIVISOR    4
        #define AUX1_PW         5
        #define AUX1_SWING      6
        #define AUX1_DELAY      7
        #define AUX2_DIVISOR    8
        #define AUX2_PW         9
        #define AUX2_SWING      10
        #define AUX2_DELAY      11
        #define AUX3_DIVISOR    12
        #define AUX3_PW         13
        #define AUX3_SWING      14
        #define AUX3_DELAY      15

    //#define FOUR_DUSPLAYS     // one display for each aux
    #ifdef FOUR_DISPLAYS
        #define MAIN_DIO 5      // 4 x 4x7-segment displays (8 digital pins)
        #define MAIN_CL 6       // actually a single display could be used (function buttons select a visible parameter, changeable with an encoder)
        #define AUX1_DIO 5      // 2 pins
        #define AUX1_CL 6
        #define AUX2_DIO 5
        #define AUX2_CL 6
        #define AUX3_DIO 5
        #define AUX3_CL 6
    #endif

    #define SINGLE_DISPLAY
    #ifdef SINGLE_DISPLAY
        #define MAIN_DISPLAY_DIO 9      // 4 x 4x7-segment displays (8 digital pins)
        #define MAIN_DISPLAY_CL 10       // actually a single display could be used (function buttons select a visible parameter, changeable with an encoder)
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
        #define TAP_POLARITY RISING

    #endif
                            // 15 to 11 pins required
#endif