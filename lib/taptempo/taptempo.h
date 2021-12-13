#pragma once
#ifndef TAPBUTTON_H
#define TAPBUTTON_H  
#include <Arduino.h>
#include <MD_UISwitch.h>

class TapTempo {  
    public:
    TapTempo(uint8_t, long, long, uint8_t, uint16_t ppqn = 24);     // TapTempo (pin, minBPM, maxBPM, tapPolarity)     
    bool check();                                                   //  true if user has finished tapping the new tempo
    int newTempo;                                                   // 
    bool isHeld;                                                    //  used for SHIFT button behaviour 
                        
    private:
    long calculateIntervalMicroSecs(long _bpm);
    
    const uint8_t EXIT_MARGIN = 120;                                // acceptable tap interval deviation, in %
    const uint8_t MINIMUM_TAPS = 3;
    const uint8_t TAP_BUTTON_ACTIVE = LOW;
    
    MD_UISwitch_Digital tapButton;                                  // the button
    MD_UISwitch::keyResult_t buttonState;

    long now;                                                       //  Actual processing happens here
    volatile long lastTapTime; 
    volatile long firstTapTime;
    volatile long timesTapped;
    long minimalTapInterval;                                        //  we'll need a single class instance
    long maximumTapInterval;                                        //  and the attachInterrupt() works only with static functions
    volatile long avgTapInterval;
    static void tapInput(); 
    long rounding(long);
};
#endif