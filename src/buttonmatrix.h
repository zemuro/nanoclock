#pragma once
#ifndef PHYSICALINTERFACE_H
#define PHYSICALINTERFACE_H
#include <Arduino.h>
#include <MD_UISwitch.h>
#include <MD_REncoder.h>
#include <GyverTM1637.h>

class PhysicalInterface{
    
    public:
    PhysicalInterface(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t); // PhysicalInterface(uint8_t _number, uint8_t _pinClk, uint8_t _pinKey, uint8_t _pinRST);
    
    bool checkButtons(bool);
    bool checkEncoder();
    void updateDisplay();
    uint8_t option;

    int8_t encoderValue;
    
    private:
    uint8_t encoderData;
    uint8_t encoderSpeed;
    const uint16_t ENCODER_PERIOD = 150;
    MD_UISwitch_4017KM buttons;
    MD_UISwitch::keyResult_t key;
    MD_REncoder encoder;
    GyverTM1637 display;

    int8_t adaptiveChange(uint8_t, uint8_t);

    enum Constants{
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
};


#endif