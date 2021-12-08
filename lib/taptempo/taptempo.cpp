#include "taptempo.h"

TapTempo::TapTempo(uint8_t pin, long minBpm, long maxBpm, uint8_t tapPolarity): tapButton(pin, tapPolarity){
    minimalTapInterval = calculateIntervalMicroSecs (maxBpm) * 24;
    maximumTapInterval = calculateIntervalMicroSecs (minBpm) * 24;
    now = micros();
    tapButton.begin();
    firstTapTime = 0;
    lastTapTime = 0;
    timesTapped = 0;
    isHeld = false;
    }

long TapTempo::calculateIntervalMicroSecs(long _bpm) {          // Take care about overflows!
//return 60L * 1000 * 1000 * 10 / _bpm / CLOCKS_PER_BEAT;        // ok
return 600000000/(24*_bpm);
}

bool TapTempo::check(){                                           /* Handle tapping of the tap tempo button*/
  //Serial.println("CHECK!");
  buttonState = tapButton.read();                                 /* CheckTapButton() returns true if the new tempo is ready*/
  now = micros();
  switch (buttonState)
  {
    case MD_UISwitch::KEY_NULL: {
      isHeld = false;
      //Serial.println("KEY NULL");
      return false;
      break;
    }
    case MD_UISwitch::KEY_UP: {
      isHeld = false;                                               // Hold determines the OPTION key behaviour
      //Serial.println("not held!");
      //Serial.println("KEY UP");
      //lastTapTime = now;
      return false;
      break;
    }
    case MD_UISwitch::KEY_DOWN: {                                 // At last, a keypress
    Serial.println("KEY DOWN");
    isHeld = true;
    Serial.println("ISHELD!");
    long now = micros();
  if (now - lastTapTime < minimalTapInterval) {
      Serial.println("DEBOUNCE!");
      Serial.print("now - lastTapTime =");
      Serial.println(now - lastTapTime );
      Serial.print("minimalTapInterval =");  
      Serial.println(minimalTapInterval); 
    return false;     // Debounce
    break;
  }

  if (now - lastTapTime < 0){
    lastTapTime = now;
    timesTapped = 0;
    Serial.println ("Negative time!");
    return false;
  }

  if (timesTapped == 0) {
    firstTapTime = now;
    Serial.print("first ");
  }
    timesTapped++;
  if (timesTapped < MINIMUM_TAPS){ 
    lastTapTime = now;
    Serial.println("Tap New lastTime!");
    }

    if (timesTapped > 0 && timesTapped < MINIMUM_TAPS && (now - lastTapTime) > maximumTapInterval) {
    // Single taps, not enough to calculate a BPM -> ignore!
    //    Serial.println("Ignoring lone taps!");
    Serial.println("SINGLE tap!");
      Serial.print("now - lastTapTime =");
      Serial.println(now - lastTapTime );
      Serial.print("maximumTapInterval =");  
      Serial.println(maximumTapInterval); 
      timesTapped = 0;
      //lastTapTime = now;
      return false;
  } else if (timesTapped >= MINIMUM_TAPS) {
                    Serial.println("Enough taps!");
                    Serial.print("now - lastTapTime =");
                    Serial.println(now - lastTapTime );
                    Serial.print("maximumTapInterval =");  
                    Serial.println(maximumTapInterval); 
    long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
                    Serial.print("avgTapInterval =");  
                    Serial.println(avgTapInterval); 
    if ((now - lastTapTime) > (avgTapInterval * EXIT_MARGIN / 100)) {
                          Serial.print("asderval =");  
                    Serial.println(avgTapInterval * EXIT_MARGIN / 100); 
                  Serial.println("Good timing!!");
      newTempo = ((60L * 1000 * 1000 * 5 / avgTapInterval)/10)*10;
      lastTapTime = now;
      timesTapped++;
      return true;
      }
      timesTapped = 0;
      //lastTapTime = now;
      return false;
  }
    /*
      if ((now - lastTapTime) < minimalTapInterval){                // debounce
        return false;
      }

      if (timesTapped == 0) {
      firstTapTime = now;
      lastTapTime = now;
      timesTapped++;
      return false;
      }
      
      //lastTapTime = now;
      //isHeld = true;
      
      if (timesTapped > 0 && timesTapped < MINIMUM_TAPS && (now - lastTapTime) > maximumTapInterval) {  // Single taps, not enough to calculate BPM -> ignore!
                                                           
        isHeld = true;   
        Serial.print("Single tap,  timesTapped =");  
        Serial.println(timesTapped); 
        Serial.print("now =");
        Serial.println(now );
        Serial.print("lastTapTime =");
        Serial.println(lastTapTime );
        Serial.print("now - lastTapTime =");
        Serial.println(now - lastTapTime );
        Serial.print("maximumTapInterval =");  
        Serial.println(maximumTapInterval); 
        Serial.print("minimalTapInterval =");  
        Serial.println(minimalTapInterval); 
        timesTapped = 0;
        lastTapTime = now;
        return false;
        break;
        }
        
        if (timesTapped >= MINIMUM_TAPS) {                              // enough taps for calculating a new tempo
          avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
          Serial.print("Enough taps,  timesTapped =");  
          Serial.println(timesTapped); 
          Serial.print("now =");
          Serial.println(now );
          Serial.print("lastTapTime =");
          Serial.println(lastTapTime );
          Serial.print("firstTaptime =");
          Serial.println(firstTapTime );
          Serial.print("now - lastTapTime =");
          Serial.println(now - lastTapTime );
          Serial.print("avgTapInterval =");  
          Serial.println(avgTapInterval); 
          Serial.print("maximumTapInterval =");  
          Serial.println(maximumTapInterval); 
          Serial.print("avgTapInterval * EXIT_MARGIN / 100 =");  
          Serial.println(avgTapInterval * EXIT_MARGIN / 100); 
        
          timesTapped = 0;
          if ((now - lastTapTime) > (avgTapInterval * EXIT_MARGIN / 100)) {    // If taps are consistent enough
          newTempo = 60L * 1000 * 1000 * 10 / avgTapInterval;               // Convert interval to tempo in BPM
          //newTempo = 800;
          isHeld = true; 
          lastTapTime = now;                                                     //
          return true;
        } else{
          timesTapped = 0;                                                  // Reset taps counter
          isHeld = true;
          lastTapTime = now;
          return false;
        }
        lastTapTime = now;
        }                                                            // not enough taps
        return false;  
        
      */
      //lastTapTime = now;
    break;
    }
    default: break;
  }
  return false;
};