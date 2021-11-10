#include <Arduino.h>
#include "displays.h"
using namespace Nanoclock;

void init(){

}

Displays::Displays (int _mainDio, int _mainClk, int _aux1Dio, int _aux1Clk, int _aux2Dio, int _aux2Clk, int _aux3Dio, int _aux3Clk){
    GyverTM1637 mainDisp(_mainDio, _mainClk);
    GyverTM1637 aux1Disp(_aux1Dio, _aux1Clk);
    GyverTM1637 aux2Disp(_aux2Dio, _aux2Clk);
    GyverTM1637 aux3Disp(_aux3Dio, _aux3Clk);
}

void Displays::clear(){
  mainDisp.clear();
  aux1Disp.clear();
  aux2Disp.clear();
  aux3Disp.clear();
}