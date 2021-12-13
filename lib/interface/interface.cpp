#include "interface.h"
#include <string.h>

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
        2/1     192 pulses
        9/4     180 pulses
        7/4     168 pulses
        3/2     144 pulses     1d
        11/8    132 pulses   11.8
        2/1T    128 pulses    2T
        5/4     120 pulses    5.4
        1/1     96 pulses      1
        9/8     90 pulses     9.8
        7/8     84 pulses     7.8
        3/4     72 pulses   1/2d
        11/16   66 pulses   11.16
        1/1T    64 pulses     1T      
        5/8     60 pulses     5.8
        1/2     48 pulses    1/2
        9/16    45 pulses    9.16
        7/16    42 pulses    7.16
        3/8     36 pulses   1/4d
        1/2T    32 pulses   1/2T
        5/16    30 pulses    5.16
        1/4     24 pulses   1/4
        3/16    18 pulses   1/8d
        1/4T    16 pulses   1/4T
        1/8     12 pulses    1/8
        3/32    9 pulses    1/16d
        1/8T    8 pulses    1/8T       
        1/16    6 pulses    1/16
        1/16T   4 pulses    1/16T
        1/32    3 pulses    1/32
        1/32T   2 pulses    /32T


*/
const long noteToPulses[] = {
  2,    //  0   = 1.32T
  3,    //  1   = 1.32
  4,    //  2   = 1.16T
  6,    //  3   = 1.16
  8,    //  4   = .8t
  9,    //  5   = 1.16d
  12,   //  6   = 1.8
  16,   //  7   = 1.4T
  18,   //  8   = 1.8d
  24,   //  9   = 1.4
  30,   //  10   = 5.16
  32,   //  11  = 1.2T
  36,   //  12  = 1.4d 
  42,   //  13  = 7.16
  45,   //  14  = 9.16
  48,   //  15  = 1.2
  60,   //  16  = 5.8
  64,   //  17  = 1T
  66,   //  18  = 11.16
  72,   //  19  = 1.2d
  84,   //  20  = 7.8
  90,   //  21  = 9.8
  96,   //  22  = 1
  120,  //  23  = 5.4
  128,  //  24  = 2t
  132,  //  25  = 11.8
  144,  //  26  = 1.d
  168,  //  27  = 7.4
  180,  //  28  = 9.4
  192,  //  29  = 2
  240,  //  30  = 5.2
  256,  //  31  = 2T
  264,  //  32  = 11.4
  288,  //  33  = 3
  336,  //  34  = 7.2
  384,  //  35  = 4
  432,  //  36  = 9.2
  480,  //  37  = 5
  528,  //  38  = 11.2
  576,  //  39  = 6
  768   //  40  = 8
};

const uint8_t dots [4] = {
  0b00000000,   //  0
  0b10000000,   //  1
  0b01000000,   //  2
  0b00100000    //  3
};



const uint8_t characterToSegment[] = {
  // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01010000,    // t     10
  0b01011110,    // d   - 11
  0b00000000,    // [space] = 12
  };

  const uint8_t noteToDisplay[41][5] = {
  {12,  3,  2,  10, 1},   //  0   = .32T
  {12,  12, 3,  2,  2},   //  1   = .32
  {12,  1,  6,  10, 1},   //  2   = .16T
  {12,  12, 1,  6,  2},   //  3   = .16
  {12,  12, 8,  10, 2},   //  4   = .8t
  {12,  1,  6,  11, 1},   //  5   = .16d
  {12,  12, 12, 8,  3},   //  6   = .8
  {12,  12, 4,  10, 2},   //  7   = .4T
  {12,  12, 8,  11, 2},   //  8   = .8d
  {12,  12, 12, 4,  3},   //  9   = .4
  {12,  5,  1,  6,  2},   //  10  = 5.16
  {12,  12, 2,  10, 2},   //  11  = .2T
  {12,  12, 4,  11, 2},   //  12  = .4d 
  {12,  7,  1,  6,  2},   //  13  = 7.16
  {12,  9,  1,  6,  2},   //  14  = 9.16
  {12,  12, 12, 2,  3},   //  15  = .2
  {12,  12, 5,  8,  3},   //  16  = 5.8
  {12,  12, 1,  10, 0},   //  17  = 1T
  {1,   1,  1,  6,  2},   //  18  = 11.16
  {12,  12, 2,  11, 2},   //  19  = .2d
  {12,  12, 7,  8,  3},   //  20  = 7.8
  {12,  12, 9,  8,  3},   //  21  = 9.8
  {12,  12, 12, 1,  0},   //  22  = 1
  {12,  12, 5,  4,  3},   //  23  = 5.4
  {12,  12, 2,  10, 0},   //  24  = 2t
  {12,  1,  1,  8,  3},   //  25  = 11.8
  {12,  12, 1,  11, 0},   //  26  = 1d
  {12,  12, 7,  4,  3},   //  27  = 7.4
  {12,  12, 9,  4,  3},   //  28  = 9.4
  {12,  12, 12, 2,  0},   //  29  = 2
  {12,  12, 5,  2,  3},   //  30  = 5.2
  {12,  12, 2,  10, 0},   //  31  = 2T
  {12,  1,  1,  4,  3},   //  32  = 11.4
  {12,  12, 12, 3,  0},   //  33  = 3
  {12,  12, 7,  2,  3},   //  34  = 7.2
  {12,  12, 12, 4,  0},   //  35  = 4
  {12,  12, 9,  2,  3},   //  36  = 9.2
  {12,  12, 12, 5,  0},   //  37  = 5
  {12,  1,  1,  2,  3},   //  38  = 11.2
  {12,  12, 12, 6,  0},   //  39  = 6
  {12,  12, 12, 8,  0}    //  40  = 8
  };

PhysicalInterface::PhysicalInterface(uint8_t _number, uint8_t _pinClk, uint8_t _pinKey, uint8_t _pinRST, uint8_t _encA, uint8_t _encB, uint8_t _cl, uint8_t _dio)://
buttons(_number, _pinClk, _pinKey, _pinRST),// 
encoder(_encA, _encB), //
display(_cl, _dio), //
displayData { 0xff, 0xff, 0xff, 0xff }{

    buttons.begin();
    buttons.enableDoublePress (false);
    buttons.enableLongPress (false);
    buttons.enableRepeat (false);
    buttons.enableRepeatResult (false);
    encoder.begin();
    encoder.setPeriod(ENCODER_PERIOD);
    display.setBrightness(255);
    currentMode = 0;

       
}

void PhysicalInterface::setDot(bool _dot){
  showBpm(lastTempo, _dot);
    return;
   }

void PhysicalInterface::displayValue(uint8_t _mode, long newValue, uint8_t output, bool dot){
  switch (_mode)
  {
    case TEMPO:
      showBpm (newValue, dot);
      lastTempo = newValue;
      currentMode = TEMPO;
      return;
      break;

    case NOTE:
      showNote (newValue);
      lastNote[output] = newValue;
      currentMode = NOTE;
      return;
    break;

    case SWING:
      showNumber (newValue);
      lastSwing[output] = newValue;
      currentMode = SWING;
      return;
    break;

    case PhysicalInterface::PW:
      showNumber(newValue);
      lastPW[output] = newValue;
      currentMode = PW;
      return;
    break;
   default:
   return;
    break;
  }
}

void PhysicalInterface::showBpm(long tempo, bool dot){
  switch (dot)
  {
  case true:
    display.showNumberDecEx(tempo, 0b00100000);
    //showNote(23);
    return;
    break;
  
  default:
    display.showNumberDecEx(tempo, 0b00000000);
    //showNote(31);
    return;
    break;
  }
}

void PhysicalInterface::showNote(uint8_t note){

  for(uint8_t i = 0; i < 4; i++){
    displayData [i] = characterToSegment[noteToDisplay[note][i]];
  }
  if(noteToDisplay[note][4] != 0)
	{
    uint8_t dotRegister = dots[noteToDisplay[note][4]];
    for(uint8_t i = 0; i < 4; ++i){
    displayData[i] |= (dotRegister & 0x80);
    dotRegister <<= 1;
    }
	}
  display.setSegments(displayData);
}


bool PhysicalInterface::checkButtons(bool _shift){
    key = buttons.read();                       // let's check out these buttons (will move this code to some class later)
  if (key != MD_UISwitch::KEY_NULL){            // something happened
    if (key == MD_UISwitch::KEY_UP)             // oh, a depressed button
      {                                         // nothing to see here
        return false;
      }; 
    if (key == MD_UISwitch::KEY_DOWN){          // some button was pressed!
        uint8_t keyNumber = buttons.getKey();   // let's find out which button
        option = keyNumber + 16 * _shift;       // returns keycodes 0..15 if _shift isn't pressed or 16..32 otherwise
      return true;                              // == N E A T ==
    }        
  }
      return false;
}


int8_t PhysicalInterface::adaptiveChange (uint8_t _direction, uint8_t _speed){
    
  increment = 1;                           // By default we are changing some value by 1
  
  if (_speed > 55){                                // By turning the encoder very fast, we are incrementing/decrementing a value by 4
    increment = 5;
  }else if (_speed >35){                             // Moderately fast rotation - inc/dec by 2
    increment = 4;
  }else if (_speed > 25){
    increment = 3;
  }else if (_speed > 15){
    increment = 2;
  }
  
  if (_direction == DIR_CW) return increment;      // return a positive increment if rotating clockwise
  return -increment;                              //
  }

bool PhysicalInterface::checkEncoder(){
    encoderData = encoder.read();                       //
  if (encoderData){
    encoderSpeed = encoder.speed(); 
    encoderValue = adaptiveChange(encoderData, encoderSpeed);
    return true;
    }
    return false;
}