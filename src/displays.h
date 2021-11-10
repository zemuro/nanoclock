/*
        Well, we need to interface 3 or 4 7-segment LED displays, 4 digits each
        1. the master display (shows bpm, some other info)
        2, 3, 4 - A display for each of the out channels. (shows divisor value)

        For now, i'll use readily available TM1637-based leds

        it will use 8 digital pins (4 pairs of CLK and DIO signals)
*/

#pragma once
#ifndef NANOCLOCK_H
#define NANOCLOCK_H    
#include <GyverTM1637.h>

namespace Nanoclock{

class Displays{
        private:
        GyverTM1637 mainDisp();
        GyverTM1637 aux1Disp();
        GyverTM1637 aux2Disp();
        GyverTM1637 aux3Disp();

        public:

        Displays (int _mainDio, int _mainClk, int _aux1Dio, int _aux1Clk, int _aux2Dio, int _aux2Clk, int _aux3Dio, int _aux3Clk);

        void init();
        void clear();

};

};
#endif