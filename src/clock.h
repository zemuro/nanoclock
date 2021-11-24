#pragma once
#ifndef CLOCK_H
#define CLOCK_H    
#include <TimerOne.h>
#include "outputs.h"
#include <Arduino.h>


#define DEFAULT_TEMPO 1000



    class Clock{
       //public:
       // Clock ();                                             // a class constructor
        private:
       
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