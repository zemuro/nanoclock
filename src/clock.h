#pragma once
#ifndef CLOCK_H
#define CLOCK_H    
#include <TimerOne.h>


    #define MAIN 0
    #define AUX1 1
    #define AUX2 2
    #define AUX3 3

    #define TEMPO   0
    #define DIVISOR 1
    #define PW      2
    #define SWING   3
    #define DELAY   4

    class Clock{

        private:                                                //
        static long calculateIntervalMicroSecs (uint8_t);
        //static uint8_t clocksPerBeat;
        static long intervalMicroseconds;
        static void update(uint8_t);
        static uint8_t bpm;                         // bpm is in tenths of BPM
        static void sendClock();                    // all the magic happens here
        static bool playing;

        static long mainCounter;                    // incremental counters
        static long aux1Counter;
        static long aux2Counter;
        static long aux3Counter;
        static long mainPeriod;                     // period lengths, set by divisors
        static long aux1Period;
        static long aux2Period;
        static long aux2Period;

        static uint8_t mainPW;
        static uint8_t mainSwing;
        static uint8_t auxDiv1;
        static uint8_t auxDiv2;
        static uint8_t auxDiv3;
        static uint8_t auxPW1;
        static uint8_t auxPW2;
        static uint8_t auxPW3;
        static uint8_t auxSwing1;
        static uint8_t auxSwing2;
        static uint8_t auxSwing3;
        static uint8_t auxDelay1;
        static uint8_t auxDelay2;
        static uint8_t auxDelay3;
        //TimerOne timer1;
        
        public:
        Clock ();      // a class constructor

        static void initialize (uint8_t);
        static void reset ();
        static void startStop ();
        static void setBpm (uint8_t);

        /* static void setDivisor (uint8_t);
        static void setMainPW (uint8_t);
        static void setSwing (uint8_t);*/

        //  changeParameter (targer, parameter, value)
        static void changeParameter (uint8_t , uint8_t, char);

};
#endif