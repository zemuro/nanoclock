#pragma once
#ifndef CLOCK_H
#define CLOCK_H    
#include <TimerOne.h>
#include <Arduino.h>

class outputChannel{
    
    private:

    enum Parameters: uint8_t {
        PERIOD = 0,
        DIVISOR = 1,
        PW = 2,
        SWING = 3,
        DELAY = 4
    };

    const uint8_t DEFAULT_PERIOD = 24;
    const long DEFAULT_DELAY = 0;
    const uint8_t DEFAULT_PW = 10;
    const int8_t DEFAULT_SWING = 0;

    uint8_t cnannelIndex;
    
    int halfPeriod1, halfPeriod2;           // Two half-periods for swing computation
    int8_t swing;                             // Swing: -100..100
    uint8_t pulseWidthRatio;                     // Pulse width: 0..100
    uint8_t outputPin;
    int counter;
    bool currentPeriod;                            // Selects current period
    long delay;
    long period;                             // Period in clock ticks (at 24 tick per quarter)
    int pulseWidth;
    void recalculate();                      // The magic!
    int counter1, counter2, pulseCounter;

    public:
    outputChannel ();                                               // default constructor
    outputChannel (uint8_t, uint8_t, long, char, uint8_t, long);    // outputChannel (uint8_t index, uint8_t pin, long period, char swing, uint8_t pulse_width, long delay);
    outputChannel (uint8_t, uint8_t);                               // outputChannel (channelIndex, channelPin)
    void reset ();
    void setParameter (uint8_t, uint8_t);                           // setParameter (parameter, value)
    void setParameter (uint8_t, char);                              // setParameter (parameter, value)
    void tick ();
};

class Clock{
    //public:
    // Clock ();                                             // a class constructor
    private:
        enum Channels: uint8_t{
        MAIN = 0,
        AUX1 = 1,
        AUX2 = 2,
        AUX3 = 3
    };
    const long DEFAULT_TEMPO = 1000;
    
    //static volatile long now;                             // well, the current time
    static long calculateIntervalMicroSecs (uint8_t);       // approved - convert tempo in bpm to interval in microseconds
    //static uint8_t clocksPerBeat;                         // 24 clocks per beat by default
    static long intervalMicroseconds;                       // initialize Timer1 with this, shrug.jpg
    static void updateTempo(uint8_t);                       // 
    static uint8_t bpm;                                     // bpm is in tenths of BPM
    static void sendClock();                                // all the magic happens here
    static bool running;                                    // is the clock running
    outputChannel main;
    outputChannel aux1;
    outputChannel aux2;
    outputChannel aux3;
    
    
    public:
    Clock (uint8_t, uint8_t, uint8_t, uint8_t);                               // a class constructor
    static void initialize (uint8_t);                       // set tempo, reset the counters, start the clock
    static void reset ();                                   // forcibly reset all counters
    static void startStop ();                               // flip the running flag
    static void setBpm (uint8_t);                           // translate tempo in bpm to interval in microseconds, set the timer period
    static void changeParameter (uint8_t , int8_t);
    long getTime();
    

};


#endif