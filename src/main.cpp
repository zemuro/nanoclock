#include "main.h"

PhysicalInterface physicalInterface(16, BUTTONS_2017_CLK, BUTTONS_2017_KEY, BUTTONS_2017_RST, ENC_PIN_A, ENC_PIN_B, DISPLAY_CL, DISPLAY_DIO); 
TapTempo tapButton(TAP_PIN, MIN_BPM, MAX_BPM, TAP_POLARITY);
Clock clock(OUT_MAIN_PIN, OUT1_PIN, OUT2_PIN, OUT3_PIN);

void tick()
{
    if (clock.running) {
        clock.tick();
    }
    return;
}


void setup()
{
    currentTempo = DEFAULT_TEMPO;
    Timer1.initialize(clock.intervalMicroseconds);                    // value is 1000000 by default
    setTempo(currentTempo);
    Timer1.attachInterrupt(tick);
}

void loop()
{
  if (tapButton.check()){                                             // returns true if the Tap button was pressed repeatedly
    setTempo(tapButton.newTempo);
  }
  
  if (physicalInterface.checkEncoder()){ /**/
  
    selector = physicalInterface.checkButtons(tapButton.isHeld);      // returns index of the pressed putton (0-15 or 0-15 + 16 with SHIFT held)
    
    switch (selector)
    {
    case clock.MAIN_RESET:
      clock.reset();
      break;

    case clock.MAIN_STARTSTOP:
      clock.running = !clock.running;
      break;

    default:
        clock.changeParameter (selector, physicalInterface.encoderValue);
      break;
    }

    currentTempo = currentTempo + physicalInterface.encoderValue;
    setTempo (currentTempo);
  }

}

void setTempo(long _tempo){
  Timer1.setPeriod(clock.calculateIntervalMicroSecs(_tempo));
  return;
}