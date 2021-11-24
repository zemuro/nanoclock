#pragma once
#ifndef OUTPUTS_H
#define OUTPUTS_H
#include <Arduino.h>

#define DEFAULT_PERIOD 24
#define DEFAULT_SWING 0
#define DEFAULT_PW 25
#define DEFAULT_DELAY 0

#define MAIN 0
#define AUX1 1
#define AUX2 2
#define AUX3 3

#define PERIOD  0
#define DIVISOR 1
#define PW      2
#define SWING   3
#define DELAY   4

class outputChannel{
    
    private:
    uint8_t cnannelIndex;
    uint8_t outputPin;
    int period;                             // Period in clock ticks (at 24 tick per quarter)
    int halfPeriod1, halfPeriod2;           // Two half-periods for swing computation
    char swing;                             // Swing: -100..100
    uint8_t pulseWidthRatio;                     // Pulse width: 0..100
    uint8_t outputPin;
    int counter;
    bool currentPeriod;                            // Selects current period
    int delay;
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
#endif