#include <Arduino.h>
#include "displays.h"
using namespace Nanoclock;


 DisplaysCombo::DisplaysCombo (int _mainDio, int _mainClk, int _aux1Dio, int _aux1Clk, int _aux2Dio, int _aux2Clk, int _aux3Dio, int _aux3Clk):
mainDisp(_mainDio, _mainClk), aux1Disp(_aux1Dio, _aux1Clk), aux2Disp(_aux2Dio, _aux2Clk), aux3Disp(_aux3Dio, _aux3Clk){
 
};

void DisplaysCombo::clear(){
  mainDisp.clear();
  aux1Disp.clear();
  aux2Disp.clear();
  aux3Disp.clear();
}
