#include "taptempo.h"

TapTempo::TapTempo(uint8_t pin, long minBpm, long maxBpm, uint8_t tapPolarity, uint16_t ppqn = 24): tapButton(pin, tapPolarity){
    minimalTapInterval = calculateIntervalMicroSecs (maxBpm) * ppqn;
    maximumTapInterval = calculateIntervalMicroSecs (minBpm) * ppqn;
    now = micros();
    tapButton.begin();
    firstTapTime = 0;
    lastTapTime = 0;
    Serial.println("Reset taps 1");
    timesTapped = 0;
    isHeld = false;
    }

long TapTempo::calculateIntervalMicroSecs(long _bpm) {        // Take care about overflows!
//return 60L * 1000 * 1000 * 10 / _bpm / CLOCKS_PER_BEAT;     // ok
return 600000000/(24*_bpm);
}

bool TapTempo::check(){                                       /* Handle tapping of the tap tempo button*/
  //Serial.println("CHECK!");
  buttonState = tapButton.read();                             /* CheckTapButton() returns true if the new tempo is ready*/
  now = micros();
  switch (buttonState)
  {
    case MD_UISwitch::KEY_UP: {
    isHeld = false;                                           // Hold determines the SHIFT key behaviour
      return false;
      break;
    }
    
    case MD_UISwitch::KEY_DOWN: {                             // At last, a keypress!!!!
    isHeld = true;
    if (now - lastTapTime < minimalTapInterval) {               // Debounce..
    Serial.println("debounce!");
    return false;
  }

    if (timesTapped == 0) {                                       // Is this a first tap
    Serial.println("first tap!");
      firstTapTime = now;                                         // rememner the moment!
    }
    
    if (now - lastTapTime < 0 || (timesTapped > 0 && (now - lastTapTime) > maximumTapInterval)) { // Is this a single tap
      timesTapped = 0;                      // the first condidion deals with timer overflows
      firstTapTime = now;                   // 
      Serial.println("single tap!");
      //return false;
    }

    if (timesTapped < MINIMUM_TAPS){        // A legit tap, but there's not enough taps
      lastTapTime = now;                    // Remember the time
      timesTapped++;
      Serial.println("not enough taps!");
    return false;
    }
    
  if (timesTapped >= MINIMUM_TAPS) {                                      // Ok, enough taps, we can calculate the tempo
  long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1); // Well, here goes MATH
  if ((now - lastTapTime) < (avgTapInterval * EXIT_MARGIN / 100)) {       // Is the last tap in time with previous taps
    newTempo = rounding(60L * 1000 * 1000 * 10 / avgTapInterval);                 // Yes, it is, calculate the new tempo!
    lastTapTime = now;                                                    // update the lastTapTime and increment the counter
    timesTapped++;                                                        // the general idea is you can tap as long as you wish
    Serial.println("new tempo!");
    return true;                                                          // yes! the new tempo is ready!

    } else{                                                               // Oh no, the last tap was out of time
      timesTapped = 0;                                                    // Reset the counter, the next tap will be the first
      Serial.println("out of time!");
      return false;
      }
  }
  Serial.println("fallback 1!");
  timesTapped = 0;
  return false;
  break;
  }
  default: {
  return false;
  break;}
}
  return false;
}

long TapTempo::rounding(long value){            // rounding to the nearest .5 bpm
  value = ((value * 2)/10) * 10;
  value = value /2;
  return value;
}