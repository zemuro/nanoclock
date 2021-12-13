/*	
        Nanoclock - an Arduino MIDI/TRIGGER/GATE clock
        Ruslan Mazavin, 2021
*/
#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <interface.h>
#include <clock.h>
#include <taptempo.h>
#include <TimerOne.h>
#include "configuration.h"

const int8_t tempoIncrement[] = {
    -100,
    -50,
    -10,
    -5,
    -1,
    0,
    1,
    5,
    10,
    50,
    100
};

const long DEFAULT_TEMPO = 1200;                // In 1/10'ths of BPM
const long MIN_BPM = 300;
const long MAX_BPM = 2600;

    uint8_t selector;                           // selects which value to change with encoder
    long currentTempo;
    void setTempo (long);

#endif