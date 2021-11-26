#include "interface.h"


PhysicalInterface::PhysicalInterface(uint8_t _number, uint8_t _pinClk, uint8_t _pinKey, uint8_t _pinRST, uint8_t _encA, uint8_t _encB, uint8_t _cl, uint8_t _dio):buttons(_number, _pinClk, _pinKey, _pinRST), encoder(_encA, _encB), display(_cl, _dio){
    buttons.begin();
    buttons.enableDoublePress (false);
    buttons.enableLongPress (false);
    buttons.enableRepeat (false);
    buttons.enableRepeatResult (false);
    encoder.begin();
    encoder.setPeriod(ENCODER_PERIOD);
    display.clear();
}

bool PhysicalInterface::checkButtons(bool _shift){
    key = buttons.read();                       // let's check out these buttons (will move this code to some class later)
  if (key != MD_UISwitch::KEY_NULL){            // 
    if (key == MD_UISwitch::KEY_UP)             // oh, a depressed button
      {                                         // nothing to see here
        return false;
      }; 
    if (key == MD_UISwitch::KEY_DOWN){          // Never assume nothing
        uint8_t keyNumber = buttons.getKey();   // let's find out what button
        if (_shift){                                    // a-ha, user pressed SHIFT
            if (keyNumber<Constants::COUNTER){          // a crutch  - NOT NEAT, but!
                option = keyNumber + 16 * _shift;       // keycodes 0..15 if _shift isn't pressed or 16..32 otherwise - == N E A T ==
                return true;                            
            }
        }        
        }
    }
    return false;
}

bool PhysicalInterface::checkEncoder(){
    encoderData = encoder.read();                       // let's check out these buttons (will move this code to some class later)
  if (encoderData){
    encoderSpeed = encoder.speed(); 
    encoderValue = adaptiveChange(encoderData, encoderSpeed);
    return true;
    }
    return false;
}

int8_t adaptiveChange (uint8_t direction, uint8_t speed){
    
  int8_t increment = 1;                           // By default we are changing some value by 1
  
  if (speed > 20){                                // By turning the encoder very fast, we are incrementing/decrementing a value by 4
    increment = 4;
  }
  else if (speed >6){                             // Moderately fast rotation - inc/dec by 2
    increment = 2;
  }
  
  if (direction == DIR_CW) return increment;      // return a positive increment if rotating clockwise
  return -increment;                              // hey, we need a signed type
}