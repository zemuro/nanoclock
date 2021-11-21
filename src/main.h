#pragma once
#ifndef MAIN_H
#define MAIN_H  
#include <TimerOne.h>
#include "nanoclock_configuration.h"
#include "displays.h"
#include "taptempo.h"
#include "clock.h"
#include <GyverTM1637.h>
#include <MD_UISwitch.h>
#include <MD_REncoder.h>

namespace Nanoclock{

static void updateBpm(long);


TapTempo tapbutton;
DisplaysCombo displays;

static int bpm;
static int encoderMode;
static int main_PW;
bool encoderRead;
static volatile long now;

// Encoder modes
#define MAIN_TEMPO  0           //  The default mode - editing the main tempo
#define DIVISOR_1   1           //  AUX1 divisor
#define DIVISOR_2   2
#define DIVISOR_3   3
#define MAIN_PW     4           //  main pulse width
#define PW_1        5
#define PW_2        6
#define PW_3        7
#define MAIN_SWING  8           //  swing setting
#define SWING_1     9
#define SWING_2     10
#define SWING_3     11
#define DELAY_1     12          //  aux channels delay
#define DELAY_2     13
#define DELAY_3     14
#define MAIN_DIVISOR 15         //  for future options (tap/option button)
}
#define ENCODER_PERIOD 500      //  ms

#endif