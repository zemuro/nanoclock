/*
        Well, we need to interface 3 or 4 7-segment LED displays, 4 digits each
        1. the master display (shows bpm, some other info)
        2, 3, 4 - A display for each of the out channels. (shows divisor value)

        For now, we'll use readily available TM1637-based leds

        it will use 8 digital pins (4 pairs of CLK and DIO signals)
*/

#pragma once
#ifndef DISPLAYS_H
#define DISPLAYS_H    
#include <GyverTM1637.h>

namespace Nanoclock{

class DisplaysCombo{

        public:
        DisplaysCombo (int, int, int, int, int, int, int, int);      // a class constructor

        private:                                                //
        GyverTM1637 mainDisp;                                   // the main display - bpm/other info
        GyverTM1637 aux1Disp;                                   // dividers for thr output channels
        GyverTM1637 aux2Disp;                                   // may be more    
        GyverTM1637 aux3Disp;                                   //

        public:
        
        void clear();

};

};
#endif