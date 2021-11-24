#include "taptempo.h"

TapTempo::TapTempo(uint8_t pin, long minBpm, long maxBpm, uint8_t tapPolarity): tapButton(pin, tapPolarity){
    minimalTapInterval = 60L * 1000 * 1000 * 10 / maxBpm;
    maximumTapInterval = 60L * 1000 * 1000 * 10 / minBpm;
    now = micros();
    tapButton.begin();
    firstTapTime = 0;
    lastTapTime = 0;
    timesTapped = 0;
    isHeld = false;
    }

bool TapTempo::check(){                                           /* Handle tapping of the tap tempo button*/
  buttonState = tapButton.read();                                 /* CheckTapButton() returns true if the new tempo is ready*/
  now = micros();
  switch (buttonState)
  {
    case MD_UISwitch::KEY_NULL: {
      // do nothing
      break;
    }
    case MD_UISwitch::KEY_UP: {
      isHeld = false;                                               // Hold determines the OPTION key behaviour
      break;
    }
    case MD_UISwitch::KEY_DOWN: {                                 // At last, a keypress
      if (!isHeld)                                                  // and the button has been released since last keypress
      {
        if (timesTapped > 0 && timesTapped < MINIMUM_TAPS && (now - lastTapTime) > maximumTapInterval) {  // Single taps, not enough to calculate BPM -> ignore!
        timesTapped = 0;                                                   
        isHeld = true;      
        return false;
        } else if (timesTapped >= MINIMUM_TAPS) {                              // enough taps for calculating a new tempo
        avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
        if ((now - lastTapTime) > (avgTapInterval * EXIT_MARGIN / 100)) {    // If taps are consistent enough
          newTempo = 60L * 1000 * 1000 * 10 / avgTapInterval;               // Convert interval to tempo in BPM
          isHeld = true;                                                      //
          return true;
        } else{
          timesTapped = 0;                                                  // Reset taps counter
          isHeld = true;
          return false;
        }} else{                                                            // not enough taps
        timesTapped++;
        isHeld = true;
        return false;  
        }
      }
      break;
    }      
    default: break;
  }
}