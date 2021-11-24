#pragma once
#ifndef MAIN_H
#define MAIN_H  
#include <TimerOne.h>
#include "nanoclock_configuration.h"
#include "taptempo.h"
#include "clock.h"
#include "buttonmatrix.h"

//namespace Nanoclock{

enum Modes{
        KEY_RUN       = 0,
        KEY_RESET     = 1,
        KEY_PW        = 2,
        KEY_SWING     = 3,
        AUX1_DIVISOR  = 4,
        AUX1_PW       = 5,
        AUX1_SWING    = 6,
        AUX1_DELAY    = 7,
        AUX2_DIVISOR  = 8,
        AUX2_PW       = 9,
        AUX2_SWING    = 10,
        AUX2_DELAY    = 11,
        AUX3_DIVISOR  = 12,
        AUX3_PW       = 13,
        AUX3_SWING    = 14,
        AUX3_DELAY    = 15,
        MAIN_DIVISOR  = 16,
        MAIN_TEMPO    = 17,
        OPTION_2      = 18,
        COUNTER       = 19
    };

static uint8_t bpm;
static uint8_t encoderMode;
static uint8_t main_PW;
bool encoderRead;
static uint8_t state;
static volatile uint8_t currentMode;
// static volatile long now;

// Encoder modes

//}
#define ENCODER_PERIOD 500      //  ms

#endif