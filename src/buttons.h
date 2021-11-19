#pragma once
#ifndef BUTTONS_H
#define BUTTONS_H    
namespace Nanoclock{

class Buttons           // well ,the buttons. 
                        // Reset, Run, +, -
{
private:
    int reset, run, plus, minus;
    bool reset, run, plus, minus;
public:
    Buttons(int, int, int, int);
    ~Buttons();
};

Buttons::Buttons(int _reset, int _run, int _plus, int _minus)
{
    reset = _reset; // initialize pins
    run = _run;
    plus = _plus;
    minus = _minus;
}

Buttons::~Buttons()
{
}



}
#endif