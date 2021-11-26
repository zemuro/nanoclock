#pragma once
#ifndef TAPBUTTON_H
#define TAPBUTTON_H  
#include <Arduino.h>
#include <MD_UISwitch.h>

class TapTempo {  
    public:

    TapTempo(uint8_t, long, long, uint8_t);         // TapTempo (pin, minBPM, maxBPM, tapPolarity)      
                        
    private:

    const uint8_t EXIT_MARGIN = 150;                // acceptable tap interval deviation, in %
    const uint8_t MINIMUM_TAPS = 3;
    const uint8_t TAP_BUTTON_ACTIVE = LOW;          // digital signal when switch is pressed 'on'
    
    MD_UISwitch_Digital tapButton;                  // the button
    static MD_UISwitch::keyResult_t buttonState;

    static long now;                    
    static void tapInput();                         //  Actual processing happens here
    static volatile long lastTapTime;               //  static members are singular and independent
    static volatile long firstTapTime;              //  of particular objects
    static volatile long timesTapped;
    static long minimalTapInterval;                 //  we'll need a single class instance
    static long maximumTapInterval;                 //  and the attachInterrupt() works only with static functions
    static volatile long avgTapInterval;

    public:

    bool check();                                   //  true if user has finished tapping the new tempo
    static int newTempo;                            // 
    static bool isHeld;                               //  used for SHIFT button behaviour
};
#endif