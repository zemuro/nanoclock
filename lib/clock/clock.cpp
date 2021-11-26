#include <Arduino.h>
#include "clock.h"

/*
Well, for clock operation we'll use a 24PPQN resolution.\
1||||||||||||||||||||||2|||||||||||||||||||||||3|||||||||||||||||||||||4|||||||||||||||||||||||
so 40 basic divisions will go like this:

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

Clock::Clock(uint8_t _pin1, uint8_t _pin2, uint8_t _pin3, uint8_t _pin4): main(MAIN, _pin1), aux1 (AUX1, _pin2), aux2 (AUX2, _pin3), aux3 (AUX3, _pin4){                                                 // construct and initialize an object
    Timer1.initialize(intervalMicroseconds);                    // value is 1000000 by default
    Timer1.setPeriod(calculateIntervalMicroSecs(DEFAULT_TEMPO));
    Timer1.attachInterrupt(Clock::sendClock);
    main.reset();
    aux1.reset();
    aux2.reset();
    aux3.reset();
}   

long Clock::getTime(){
  return 0L;
}

long Clock::calculateIntervalMicroSecs(uint8_t _bpm) {          // Take care about overflows!
  return 60L * 1000 * 1000 * 10 / bpm / CLOCKS_PER_BEAT;        // ok
}

void Clock::updateTempo (uint8_t bpm){
    long interval = calculateIntervalMicroSecs(bpm);
    Timer1.setPeriod(interval);
}

void Clock::reset (){
    running = false;
    running = true;
}

void Clock::startStop(){
     if (!running) {
    Serial.println("Start playing");
    //Serial1.write(MIDI_START);
  } else {
    Serial.println("Stop playing");
    //Serial1.write(MIDI_STOP);
  }
  running = !running;
}

/* Period = 12

 swing = 0, pw = 25% 
 counter                00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 00 01 02    2*period
 output                 |  |  |  _  _  _  _  _  _  _  _  _  |  |  |  _  _  _  _  _  _  _  _  _  |  |  |     swing = 0, max pw = (period-swing), pw = 0.25*12 = 3
 **                                                                                                         swing [0..100], dislocation [0..0.5p] * p, (!!!)
 **                                                                                                         pulse width [0..100] -> [0..p-dislocation] (!!!)
 **                                                                                                         so firstly we take a period
 **                                                                                                         calculate swinged values P1, P2
 **                                                                                                         
 swing = 0, pw = 75% 
 counter                00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 00 01 02    pw = pw(preiod-swing) = 0.75*12 = 8
 output                 |  |  |  |  |  |  |  |  |  _  _  _  |  |  |  |  |  |  |  |  |  _  _  _  |  |  |

 swing = 17%
 counter                00 01 02 03 04 05 06 07 08 09 00 01 02 03 04 05 06 07 08 09 10 11 12 13 00 01 02    max dislocation = period/2
 output                 |  |  |  _  _  _  _  _  _  _  |  |  |  _  _  _  _  _  _  _  _  _  _  _  |  |  |     dislocation = swing*period = 0.17*12 = 2.04
 **                                                                                                         first half-counter  = period - dislocation = 12 - 2 = 10
 **                                                                                                         second half-counter = period + dislocation = 12 + 2 = 14
 **                                                                                                         maxPW1 = (first half-counter - 1) = 10 - 1 = 9
 **                                                                                                         PW1 = pw * maxPW1
 **                                                                                                         PW2 = pw * maxPW2 ?? 

 swing = 100%,  pw = 25%
 counter                00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 00 01 02    if (pw < 0.49), PW1 = PW2 = period * pw = 12*25 = 3
 output                 |  |  |  _  _  _  |  |  |  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  |  |  |     

 swing = 100%,  pw = 100%
 counter                00 01 02 03 04 05 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 00 01 02    PW1 = pw * maxPW1 = 1 * 5 = 5, PW2 = pw * maxPW2 = 1 * 17 = 17
 output                 |  |  |  |  |  _  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  _  |  |  |     

********* OR ************

 swing = 100%,  pw = 100%
 counter                00 01 02 03 04 05 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 00 01 02    PW1 = pw * maxPW1 = 1 * 5 = 5, PW2 = PW1 = 5
 output                 |  |  |  |  |  _  |  |  |  |  |  _  _  _  _  _  _  _  _  _  _  _  _  _  |  |  |     


*/
outputChannel::outputChannel(uint8_t _index, uint8_t _pin, long _period, char _swing, uint8_t _pw, long _delay){
    cnannelIndex = _index;
    period = _period;
    swing = _swing;
    delay = _delay;
    pulseWidthRatio = _pw;
    halfPeriod1 = period / 2;
    halfPeriod2 = period - halfPeriod1; 
    outputPin = _pin;
    pinMode(outputPin, OUTPUT);
    counter = 0;
    currentPeriod = false;
    pulseCounter = 0;
    };

outputChannel::outputChannel(uint8_t _index, uint8_t _pin): swing(DEFAULT_SWING), pulseWidthRatio(DEFAULT_PW), delay(DEFAULT_DELAY), period(DEFAULT_PERIOD){
    cnannelIndex = _index;
    halfPeriod1 = period / 2;
    halfPeriod2 = period - halfPeriod1;
    outputPin = _pin;
    pinMode(outputPin, OUTPUT);
    counter = 0;
    currentPeriod = false;
    pulseCounter = 0;
    };

void outputChannel::reset(){
    counter = 0;
    currentPeriod = false;
    pulseCounter = 0;
    return;
}

void outputChannel::setParameter (uint8_t _param, uint8_t _val){
    switch (_param)
    {
    case PERIOD: {
        period = _val;
        recalculate();
        break;
    }
    case DIVISOR: {
        period = _val;
        recalculate();
        break;
    }
    case SWING: {
        swing = (char) _val;
        recalculate();
        break;
    }
    case PW: {
        pulseWidthRatio = _val;
        recalculate();
        break;
    }
    case DELAY: {
        delay = _val;
        recalculate();
        break;
    }
    default:
        break;
    }

}

void outputChannel::recalculate(){
    if (swing == 0){                                         // Zero swing
        halfPeriod1 = period/2;                             // theoretically, our half-periods should be equal, but we're  
        halfPeriod2 = period - halfPeriod1;                 // dealing with integers here, seems safer this way
        pulseWidth = (halfPeriod1 * pulseWidthRatio)/100;   // serious ARITHMETICS here
        return;
    }
    else if (swing >0){                                     // positive swing
        halfPeriod2 = (period * swing) / 400;               // swing = 100 - second half is 1/4 * period
        halfPeriod1 = period = halfPeriod2;
        pulseWidth = (halfPeriod2 * pulseWidthRatio) / 100;  // can't be longer than the smallest period
        return;
    }
    
    halfPeriod1 = (period * swing) / 400;                   // negative swing - first period is shorter
    halfPeriod2 = period = halfPeriod2;                     //
    pulseWidth = (halfPeriod1 * pulseWidthRatio) / 100;     // can't be longer than the smallest period (max - )
    return;
}

void outputChannel::tick(){
    if (counter1 <= halfPeriod1 && !currentPeriod){                         // we are in the first half
        if (pulseCounter <= pulseWidth && pulseCounter < halfPeriod1){      // still forming a pulse and haven't reached the end of the period yet
            digitalWrite (outputPin, HIGH);                                 // here she goes
            pulseCounter++;                                                 // increment counter
            counter++;                                                      // the other counter
            return;
        }
        if (pulseCounter > pulseWidth && pulseCounter < halfPeriod1){       // still forming a zero and haven't reached the end of the period yet
            digitalWrite (outputPin, LOW);                                  //
            pulseCounter++;
            counter++;
            return;
        }
        if (counter1 == halfPeriod1){                                       // reached the last step of halfPeriod1
            if (pulseCounter > pulseWidth){                                 
                digitalWrite (outputPin, LOW);                              // form a zero
                pulseCounter = 0;
                counter = 0;                                                // reset the counter for the next half
                currentPeriod = !currentPeriod;                             // flip a flag
                return;
            }   else{                                                       // high PW - we're STILL forming a pulse
                digitalWrite (outputPin, HIGH);                             // well whatever (maybe should make an option to always leave a zero tick before the next half)
                pulseCounter = 0;                                           //
                counter = 0;                                                // reset the counters
                currentPeriod = !currentPeriod;                             // to the second half we go!
                return;
            }

        }
    }
    if (counter2 <= halfPeriod2){                                           // we're in the second half, it's safe to assume the flag is set
        if (pulseCounter <= pulseWidth && pulseCounter < halfPeriod2){      // still positive
            digitalWrite (outputPin, HIGH);
            pulseCounter++;
            counter++;
            return;
        }
        if (pulseCounter > pulseWidth && pulseCounter < halfPeriod2){       // negative
            digitalWrite (outputPin, LOW);
            pulseCounter++;
            counter++;
            return;
        }
        if (counter1 == halfPeriod1){                                       // reached the last step of halfPeriod2
            if (pulseCounter > pulseWidth){                                 
                digitalWrite (outputPin, LOW);                              // form a zero
                pulseCounter = 0;
                counter = 0;                                                // reset the counter for the next half
                currentPeriod = !currentPeriod;                             // flip a flag
                return;
            }                                                               // high PW - we're STILL forming a pulse
                digitalWrite (outputPin, HIGH);                             // well whatever (maybe should make an option to always leave a zero tick before the next half)
                pulseCounter = 0;                                           //
                counter = 0;                                                // reset the counters
                currentPeriod = !currentPeriod;                             // to the second half we go!
                return;
            
        }  
    } 
};