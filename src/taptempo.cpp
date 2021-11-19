#include <Arduino.h>
#include "taptempo.h"
#include <TimerOne.h>
#include "main.h"
using namespace Nanoclock;

TapButton::TapButton(int pin, long minBpm, long maxBpm, int minTaps, int tapPolarity, long exitMrgn)        // we make an object
{
    minimalTapInterval = 60L * 1000 * 1000 * 10 / maxBpm;
    maximumTapInterval = 60L * 1000 * 1000 * 10 / minBpm;
    tapPin = pin;
    firstTapTime = 0;
    lastTapTime = 0;
    timesTapped = 0;
    exitMargin = exitMrgn;
    minimumTaps = minTaps;
    attachInterrupt(digitalPinToInterrupt(tapPin), TapButton::tapInput, tapPolarity);  
}

void TapButton::tapInput(){     //  a static method, every time tap happens
   if (Nanoclock::now - lastTapTime < minimalTapInterval) {     // too little time
    return;                                         // Debounce done
  }

  if (timesTapped == 0) {
    firstTapTime = now;
  }

  timesTapped++;
  lastTapTime = now;
  // Serial.println("Tap!");
}

bool TapButton::CheckTapButton(){ /* Handle tapping of the tap tempo button*/

  if (timesTapped > 0 && timesTapped < minimumTaps && (now - lastTapTime) > maximumTapInterval) {
                
    timesTapped = 0;                                                    // Single taps, not enough to calculate BPM -> ignore!
    return false;

  } else if (timesTapped >= minimumTaps) {
    avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
    if ((now - lastTapTime) > (avgTapInterval * exitMargin / 100)) {
      bpm = 60L * 1000 * 1000 * 10 / avgTapInterval;
      return true;                                                      // it's time to update bpm and reset the blinker

      // Update blinkCount to make sure LED blink matches tapped beat
      // blinkCount = ((now - lastTapTime) * 24 / avgTapInterval) % CLOCKS_PER_BEAT;

      timesTapped = 0;
    }
    return false;
  }

}