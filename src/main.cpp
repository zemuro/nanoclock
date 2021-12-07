#include "main.h"

PhysicalInterface interface(16, BUTTONS_2017_CLK, BUTTONS_2017_KEY, BUTTONS_2017_RST, ENC_PIN_A, ENC_PIN_B, DISPLAY_CL, DISPLAY_DIO); 
TapTempo tapButton(TAP_PIN, MIN_BPM, MAX_BPM, TAP_POLARITY);
Clock clock(OUT_MAIN_PIN, OUT1_PIN, OUT2_PIN, OUT3_PIN);

void tick()
{
  if (clock.running) {
        if (clock.tick()){
          //interface.setDot(true);
          return;
        }
        //interface.setDot(false);
        return;
    return;
  }
}


void setup()
{
    currentTempo = DEFAULT_TEMPO;
    Timer1.initialize(1);
    setTempo(currentTempo);
    Timer1.attachInterrupt(tick);
    //interface.updateDisplay();
}

void loop()
{
  if (tapButton.check()){                                             // returns true if the Tap button was pressed repeatedly
    setTempo(tapButton.newTempo);
    
  }
  //interface.updateDisplay();
  /*
  if (interface.checkEncoder()){
  
    selector = interface.checkButtons(tapButton.isHeld);      // returns index of the pressed putton (0-15 or 0-15 + 16 with SHIFT held)
    
    switch (selector)
    {
    case clock.MAIN_RESET:
      clock.reset();
      break;

    case clock.MAIN_STARTSTOP:
      clock.running = !clock.running;
      break;

    default:
        clock.changeParameter (selector, interface.encoderValue);
      break;
    }

    currentTempo = currentTempo + interface.encoderValue;
    setTempo (currentTempo);
  }*/
}

void setTempo(long _tempo){
  Timer1.setPeriod(clock.calculateIntervalMicroSecs(_tempo));
  //interface.displayValue(interface.TEMPO, _tempo, interface.MAIN, true);
  for (uint8_t i = 0; i < 41; i++){
        interface.displayValue(interface.NOTE, i);
        delay(1000);
  }

  return;
}