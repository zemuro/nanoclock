#pragma once
#ifndef TAPBUTTON_H
#define TAPBUTTON_H  

#define EXIT_MARGIN 150
#define MINIMUM_TAPS 3

namespace Nanoclock{

class TapTempo {        
                        
private:

static void tapInput();             //  Actual processing happens here

static volatile long lastTapTime;   //  static members are singular and independent
static volatile long firstTapTime;  //  of particular objects
static volatile long timesTapped;   //
static long minimalTapInterval;     //  we'll need a single class instance
static long maximumTapInterval;     //  and the attachInterrupt() works only with static functions
static volatile long avgTapInterval;
static int minimumTaps;
static int tapPin;
static long exitMargin;

public:
    // TapTempo (pin, minBPM, maxBPM, tapPolarity)
    TapTempo(int, long, long, int);
    static bool CheckTapButton();    //  true if user has finished tapping the new tempo
};
};
#endif