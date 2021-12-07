#pragma once
#ifndef CLOCK_H
#define CLOCK_H    
#include <Arduino.h>
//#include <TimerOne.h>


class outputChannel{
    
    private:
    const uint8_t DEFAULT_PPQN = 24;
    const long DEFAULT_DELAY = 0;
    const uint8_t DEFAULT_PW = 25;
    const int8_t DEFAULT_SWING = 50;

    uint8_t cnannelIndex;
    
    int halfPeriod1, halfPeriod2;           // Two half-periods for swing computation
    int8_t swing;                             // Swing: -100..100
    uint8_t pulseWidthRatio;                     // Pulse width: 0..100
    uint8_t outputPin;
    //int counter;
    bool secondPeriod;                            // Selects current period
    long delay;
    long period;                             // Period in clock ticks (at 24 tick per quarter)
    long pulseWidth;
    void recalculate();                      // The magic!
    long counter, pulseCounter;
    void printVals();
    long displacement;

    public:
        enum Parameters: uint8_t {
        PERIOD = 0,
        DIVISOR = 1,
        PW = 2,
        SWING = 3,
        DELAY = 4
    };
    outputChannel ();                                               // default constructor
    outputChannel (uint8_t, uint8_t, long, char, uint8_t, long);    // outputChannel (uint8_t index, uint8_t pin, long period, char swing, uint8_t pulse_width, long delay);
    outputChannel (uint8_t, uint8_t);                               // outputChannel (channelIndex, channelPin)
    void reset ();
    void changeParameter (uint8_t, int8_t);                           // setParameter (parameter, value)
    bool tick ();
};

class Clock{
    //public:
    // Clock ();                                             // a class constructor
    private:
            
    outputChannel main;
    outputChannel aux1;
    outputChannel aux2;
    outputChannel aux3;

        enum Channels: uint8_t{
        MAIN = 0,
        AUX1 = 1,
        AUX2 = 2,
        AUX3 = 3
        };
   
    static void marshall();
    const long DEFAULT_TEMPO = 1000;
    static uint8_t channelIndex;
    bool doubleTick;
    
    void updateTempo(uint8_t);                       // 
    uint8_t bpm;                                     // bpm is in tenths of BPM
    
    public:
        
    enum Options: uint8_t{
        MAIN_RESET      = 0,
        MAIN_STARTSTOP  = 1,
        AUX1_DIVISOR    = 2,
        AUX1_PW         = 3,
        AUX1_SWING      = 4,
        AUX1_DELAY      = 20,                 // shift + swing 1
        AUX2_DIVISOR    = 5,
        AUX2_PW         = 6,
        AUX2_SWING      = 7,
        AUX2_DELAY      = 23,               // shift + swing 2
        AUX3_DIVISOR    = 8,
        AUX3_PW         = 8,
        AUX3_SWING      = 10,
        AUX3_DELAY      = 26,               // shift + swing 3
        MAIN_DIVISOR    = 11,               // shift
        COUNTER         = 15
    };

    Clock (uint8_t, uint8_t, uint8_t, uint8_t);      // a class constructor
    //static Clock* instance;
    bool running;  
    long intervalMicroseconds;                       // initialize Timer1 with this, shrug.jpg
    long calculateIntervalMicroSecs (long);       // approved - convert tempo in bpm to interval in microseconds
    void init ();                                    // set tempo, reset the counters, start the clock
    void reset ();                                   // forcibly reset all counters
    void startStop ();                               // flip the running flag
    void setBpm (uint8_t);                           // translate tempo in bpm to interval in microseconds, set the timer period
    void changeParameter (uint8_t , int8_t);
    long getTime();
    bool tick();                                    // all the magic happens here

        
};

#endif