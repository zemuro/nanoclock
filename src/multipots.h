#pragma once
#ifndef MULTIPOTS_H
#define MULTIPOTS_H    

namespace Nanoclock{

    class MultiplexedPots {
        
        private:

        char _a0;                //  adress bus
        char _a1;
        char _a2;
        char _a3;
        char _adcPin;  
        int potValue;

        const int channel_bits[16][4] = {       // s0, s1, s2, s3 for each channel
        {0,  0,  0,  0}, // 0
        {1,  0,  0,  0}, // 1
        {0,  1,  0,  0}, // 2
        {1,  1,  0,  0}, // 3
        {0,  0,  1,  0}, // 4
        {1,  0,  1,  0}, // 5
        {0,  1,  1,  0}, // 6
        {1,  1,  1,  0}, // 7
        {0,  0,  0,  1}, // 8
        {1,  0,  0,  1}, // 9
        {0,  1,  0,  1}, // 10
        {1,  1,  0,  1}, // 11
        {0,  0,  1,  1}, // 12
        {1,  0,  1,  1}, // 13
        {0,  1,  1,  1}, // 14
        {1,  1,  1,  1}  // 15
        };

        void setChannel(int channel);

        public:

        MultiplexedPots(int a0, int a1, int a2, int a3, int adcpin); // the class constructor
        int potValue (int potNumber);   // read pot
        int potValue_8 (int potNumber); // read pot, return 8-bit value


    };
};
#endif  