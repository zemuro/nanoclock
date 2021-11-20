#pragma once
#ifndef CLOCK_H
#define CLOCK_H    
#include <TimerOne.h>

namespace Nanoclock{

    class Clock{

        private:                                                //
        static long calculateIntervalMicroSecs (int);
        //static int clocksPerBeat;
        static long intervalMicroseconds;
        static void update(int);
        static int bpm;                                         // tenths of BPM
        static void sendClock();
        static bool playing;
        //TimerOne timer1;
        
        public:
        Clock ();      // a class constructor

        static void reset();
        static void startStop();
        static void setBpm();
        static void setDivisor();
        static void setPwm();
        static void setSwing();

};

class OutputChannel{
        public:
        OutputChannel ();

        private:

        int channelPin;
        int channelNumber;
        int channelState;
        int lastState;

};

};
#endif