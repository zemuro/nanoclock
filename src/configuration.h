//#define ATTINY88              //  MH-Tiny ATtiny88 Micro
#define ARDUINO_UNO             //  Standard Arduino Uno
//#define ARDUINOPROMICRO       //  Arduino 


#ifdef ATTINY88

    const uint8_t BUTTONS_2017_CLK = 11;     // 4x4 button matrix, connected to 4017 -- need to rewrite library
    const uint8_t BUTTONS_2017_KEY = 12;     // or 16 buttons, connected to 2 x 4017 -- maybe should integrate the tapTempo class
    const uint8_t BUTTONS_2017_RST = 13;     // all in all, it's 3 digital pins

    #define SINGLE_DISPLAY
    #ifdef SINGLE_DISPLAY
        const uint8_t DISPLAY_DIO = 9;      // 4x7-segment display (2 digital pins)
        const uint8_t DISPLAY_CL = 10;
    #endif

    const uint8_t ENC_PIN_A = 1;            // encoder pins (2 digital pins)
    const uint8_t ENC_PIN_B = 8;
    
    const uint8_t OUT_MAIN_PIN = 4;         // Trigger/gate output pins (4 digital pins)
    const uint8_t OUT1_PIN = 5;
    const uint8_t OUT2_PIN = 6;
    const uint8_t OUT3_PIN = 7;
 

    #define TAP_TEMPO                       // Tap tempo button (1 digital pin) 
        #ifdef  TAP_TEMPO
        const uint8_t TAP_PIN = 3;               
        #define TAP_POLARITY LOW

    #endif

#endif                                      // 12 digital pins, not bad



#ifdef ARDUINO_UNO

    const uint8_t BUTTONS_2017_CLK = 11;     // 4x4 button matrix, connected to 4017 -- need to rewrite library
    const uint8_t BUTTONS_2017_KEY = 12;     // or 16 buttons, connected to 2 x 4017 -- maybe should integrate the tapTempo class
    const uint8_t BUTTONS_2017_RST = 13;     // all in all, it's 3 digital pins

    #define SINGLE_DISPLAY
    #ifdef SINGLE_DISPLAY
        const uint8_t DISPLAY_DIO = 9;      // 4x7-segment display (2 digital pins)
        const uint8_t DISPLAY_CL = 10;
    #endif

    const uint8_t ENC_PIN_A = 1;            // encoder pins (2 digital pins)
    const uint8_t ENC_PIN_B = 8;
    
    const uint8_t OUT_MAIN_PIN = 4;         // Trigger/gate output pins (4 digital pins)
    const uint8_t OUT1_PIN = 5;
    const uint8_t OUT2_PIN = 6;
    const uint8_t OUT3_PIN = 7;
 

    #define TAP_TEMPO                       // Tap tempo button (1 digital pin) 
        #ifdef  TAP_TEMPO
        const uint8_t TAP_PIN = 3;               
        #define TAP_POLARITY LOW

    #endif

#endif                                      // 12 digital pins, not bad