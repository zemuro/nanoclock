#include <Arduino.h>
#include "clock.h"

/*
Well, for clock operation we'll use a 24PPQN resolution.\
1||||||||||||||||||||||2|||||||||||||||||||||||3|||||||||||||||||||||||4|||||||||||||||||||||||
so 40 basic divisions will go like this: (oh hell, I definetely need an encoder)

        8/1     768 pulses
        6/1     576 pulses
        11/2    528 pulses
        9/2     432 pulses
        4/1     390 pulses
        7/2     336 pulses
        3/1     288 pulses
        11/4    264 pulses
        2/1T    256 pulses
        5/2     240 pulses
        2/1     195 pulses
        9/4     180 pulses
        7/4     168 pulses
        3/2     144 pulses
        11/8    132 pulses
        2/1T    128 pulses
        5/4     120 pulses
        1/1     96 pulses
        9/8     90 pulses
        7/8     84 pulses
        3/4     72 pulses
        11/16   66 pulses
        1/1T    64 pulses      
        5/8     60 pulses
        1/2     48 pulses
        9/16    45 pulses
        7/16    42 pulses
        3/8     36 pulses
        1/2T    32 pulses
        5/16    30 pulses
        1/4     24 pulses
        3/16    18 pulses
        1/4T    16 pulses
        1/8     12 pulses
        3/32    9 pulses
        1/8T    8 pulses       
        1/16    6 pulses
        1/16T   4 pulses
        1/32    3 pulses
        1/32T   2 pulses


*/

#define CLOCKS_PER_BEAT 24
#define MIDI_START 0xFA
#define MIDI_STOP 0xFC

using namespace Nanoclock;

Clock::Clock(){                                             // construct and initialize an object
    Timer1.initialize(intervalMicroseconds);                // value is 1000000 by default
    Timer1.setPeriod(calculateIntervalMicroSecs(bpm));
    Timer1.attachInterrupt(sendClock);

}

long Clock::calculateIntervalMicroSecs(int _bpm) {          // Take care about overflows!
  return 60L * 1000 * 1000 * 10 / bpm / CLOCKS_PER_BEAT;    // ok
}

void Clock::update (int bpm){
    long interval = calculateIntervalMicroSecs(bpm);
    Timer1.setPeriod(interval);
}

void Clock::startStop(){
     if (!playing) {
    Serial.println("Start playing");
    //Serial1.write(MIDI_START);
  } else {
    Serial.println("Stop playing");
    //Serial1.write(MIDI_STOP);
  }
  playing = !playing;
}