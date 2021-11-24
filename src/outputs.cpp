#include "outputs.h"

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
    if (swing = 0){                                         // Zero swing
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