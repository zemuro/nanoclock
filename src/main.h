#pragma once
#ifndef MAIN_H
#define MAIN_H  
namespace Nanoclock{

static void updateBpm(long);

TapButton tapbutton;
MultiplexedPots pots;
DisplaysCombo displays;

static int bpm;
static volatile long now;

}
#endif