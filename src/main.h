#pragma once
#ifndef MAIN_H
#define MAIN_H  
#include <TimerOne.h>
#include "nanoclock_configuration.h"
#include "displays.h"
#include "taptempo.h"
#include "clock.h"
#include <GyverTM1637.h>
namespace Nanoclock{

static void updateBpm(long);

TapButton tapbutton;
DisplaysCombo displays;

static int bpm;
static volatile long now;

}
#endif