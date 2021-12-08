#include <Arduino.h>
#include "clock.h"

#define CLOCKS_PER_BEAT 24
#define MIDI_START 0xFA
#define MIDI_STOP 0xFC
    
//Clock::Clock(uint8_t _pin1, uint8_t _pin2, uint8_t _pin3, uint8_t _pin4): main(MAIN, _pin1), aux1(AUX1, _pin2), aux2(AUX2, _pin3), aux3(AUX3, _pin4){   
    Clock::Clock(uint8_t _pin1, uint8_t _pin2, uint8_t _pin3, uint8_t _pin4): main(MAIN, LED_BUILTIN), aux1(AUX1, _pin2), aux2(AUX2, _pin3), aux3(AUX3, _pin4){   
    //instance = this;                                              // construct and initialize an object
    main.reset();
    aux1.reset();
    aux2.reset();
    aux3.reset();
    running = true;
    doubleTick = false;
}   

void Clock::changeParameter(uint8_t _option, int8_t _value){
    if (_option <= 1 || _option == 16){     //main channel
        main.changeParameter (_option, _value);
        return;   
    } //else if (_option <= 4 )
}

void Clock::tick(){
    aux1.tick();
    aux2.tick();
    aux3.tick();
    main.tick();
    return;
}

long Clock::getTime(){
  return 0L;
}

long Clock::calculateIntervalMicroSecs(long _bpm) {          // Take care about overflows!
  //return 60L * 1000 * 1000 * 10 / _bpm / CLOCKS_PER_BEAT;        // ok
  return 600000000/(24*_bpm);
}

void Clock::updateTempo (uint8_t bpm){
    return;
}

void Clock::reset (){
    running = false;
    main.reset();
    aux1.reset();
    aux2.reset();
    aux3.reset();
    running = true;
    return;
}

void Clock::startStop(){
    running = !running;
    return;
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

period = 24
swing = 100
(period/4)*swing/100
period*swing / 400 = 2400/400 = 6
6*swing/100 = 6


*/
outputChannel::outputChannel(uint8_t _index, uint8_t _pin, long _period, char _swing, uint8_t _pw, long _delay){
    cnannelIndex = _index;
    period = _period * 4;
    swing = _swing;
    delay = _delay;
    pulseWidthRatio = _pw;
    halfPeriod1 = period / 2;
    halfPeriod2 = period - halfPeriod1; 
    outputPin = _pin;
    pinMode(outputPin, OUTPUT);
    counter = 0;
    secondPeriod = false;
    pulseCounter = 0;
    recalculate();
    };

outputChannel::outputChannel(uint8_t _index, uint8_t _pin): swing(DEFAULT_SWING), pulseWidthRatio(DEFAULT_PW), delay(DEFAULT_DELAY), period(DEFAULT_PPQN){
    cnannelIndex = _index;
    period = period * 2;
    halfPeriod1 = period / 2;               // 25/2 = 12 - 1 = 11 (0..11 - 12 counts)  
    halfPeriod2 = period - halfPeriod1;     // 25 - 12 = 13 - 1 = 12 (13 counts)
    outputPin = _pin;
    pinMode(outputPin, OUTPUT);
    counter = 0;
    secondPeriod = false;
    pulseCounter = 0;       
    //Serial.begin(9600);                //
    recalculate();
    };

void outputChannel::reset(){
    counter = 0;
    secondPeriod = false;
    pulseCounter = 0;
    return;
}

void outputChannel::changeParameter (uint8_t _param, int8_t _val){
    switch (_param)
    {
    case PERIOD: {
        period += _val;
        recalculate();
        break;
    }
    case DIVISOR: {
        period += _val;
        recalculate();
        break;
    }
    case SWING: {
        swing += (char) _val;
        recalculate();
        break;
    }
    case PW: {
        pulseWidthRatio += _val;
        recalculate();
        break;
    }
    case DELAY: {
        delay += _val;
        recalculate();
        break;
    }
    default:
        break;
    }

}

void outputChannel::recalculate(){
    if (swing == 0){                                            // Zero swing
        halfPeriod1 = period/2 - 1;                             // theoretically, our half-periods should be equal, but we're  
        halfPeriod2 = period - halfPeriod1 - 2;                 // dealing with integers here, seems safer this way
        pulseWidth = (halfPeriod1 * pulseWidthRatio)/100;       // serious ARITHMETICS here
        //printVals();
        return;
    }
    else if (swing >0){                                         // positive swing
        displacement = (period * swing) /400;                   // swing = 50 - second half is 0.25 * period ((period/2)/4)*swing / 100 = period*swing/800
        halfPeriod2 = period/2 - 1 - displacement;              // swing = 25, hp2 = 24*25 = 600/400 = 1.5
        halfPeriod1 = period - halfPeriod2 - 2;                 // 100*12/800 = 1200/800 = 1,5
        pulseWidth = (halfPeriod2 * pulseWidthRatio) / 100;     // can't be longer than the smallest period
        //printVals();
        return;
    }
    swing = -swing;                                             // (12 * 30) / 400 = 360/400 = 0!!
    halfPeriod1 = (period * swing) / 400 - 1;                   // negative swing - first period is shorter
    halfPeriod2 = period - halfPeriod2 - 1;                     //
    pulseWidth = (halfPeriod1 * pulseWidthRatio) / 100;         // can't be longer than the smallest period (max - )
    printVals();
    return;
}
void outputChannel::printVals(){
    Serial.print("\nPeriod =");
    Serial.print(period);
    Serial.print("\thalf1 = ");
    Serial.print(halfPeriod1);
    Serial.print("\thalf2 = ");
    Serial.print(halfPeriod2);
    Serial.print("\tswing = ");
    Serial.print(swing);
    Serial.print("\tpw = ");
    Serial.print(pulseWidth);
    Serial.print("\tdisplacement = ");
    Serial.print(displacement);
    return;
}
bool outputChannel::tick(){
  /* if (counter <= halfPeriod1){
        digitalWrite (outputPin, HIGH);
        counter++;
        return;
    } else if (counter <= (halfPeriod1 + halfPeriod2)){
        digitalWrite (outputPin, LOW);
        counter++;
    } else {
        digitalWrite (outputPin, LOW);
        counter = 0;
    }*/
    if (!secondPeriod){
        if(counter < halfPeriod1){
            if (pulseCounter <= pulseWidth){        // still forming a pulse and haven't reached the end of the period yet
            digitalWrite (outputPin, HIGH);         // here she goes
            pulseCounter++;
            counter++;
            return true;
        }
            if (pulseCounter > pulseWidth){       // still forming a zero and haven't reached the end of the period yet
                digitalWrite (outputPin, LOW);                                  //
                pulseCounter++;
                counter++;
                return false;
            }
        }
        if (counter == halfPeriod1){                                       // reached the last step of halfPeriod1
            if (pulseCounter > pulseWidth){                                 
                digitalWrite (outputPin, LOW);                              // form a zero
                pulseCounter = 0;
                counter = 0;                                                // reset the counter for the next half
                secondPeriod = !secondPeriod;                             // flip a flag
                return false;
            }   else{                                                       // high PW - we're STILL forming a pulse
                digitalWrite (outputPin, HIGH);                             // well whatever (maybe should make an option to always leave a zero tick before the next half)
                pulseCounter = 0;                                         //
                counter = 0;                                              // reset the counters
                secondPeriod = !secondPeriod;                             // to the second half we go!
                return true;
            }
        }
    }

    if (counter < halfPeriod2){                                             // we're in the second half, it's safe to assume the flag is set
        if (pulseCounter <= pulseWidth){                                      // still positive
            digitalWrite (outputPin, HIGH);
            pulseCounter++;
            counter++;
            return true;
        }
        if (pulseCounter > pulseWidth){       // negative
            digitalWrite (outputPin, LOW);
            pulseCounter++;
            counter++;
            return false;
        }
    }
    //    if (counter == halfPeriod2){                                        // reached the last step of halfPeriod2
            if (pulseCounter > pulseWidth){                                 
                digitalWrite (outputPin, LOW);                              // form a zero
                pulseCounter = 0;
                counter = 0;                                                // reset the counter for the next half
                secondPeriod = !secondPeriod;                             // flip a flag
                return false;
            }                                                               // high PW - we're STILL forming a pulse
                digitalWrite (outputPin, HIGH);                             // well whatever (maybe should make an option to always leave a zero tick before the next half)
                pulseCounter = 0;                                           //
                counter = 0;                                                // reset the counters
                secondPeriod = !secondPeriod;                             // to the second half we go!
                return true;
}