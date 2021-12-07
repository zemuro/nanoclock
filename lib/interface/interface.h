#pragma once
#ifndef PHYSICALINTERFACE_H
#define PHYSICALINTERFACE_H
#include <Arduino.h>
#include <MD_UISwitch.h>
#include <MD_REncoder.h>
#include <TM1637Display.h>

class PhysicalInterface{
    
    public:
    PhysicalInterface(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t); // PhysicalInterface(uint8_t _number, uint8_t _pinClk, uint8_t _pinKey, uint8_t _pinRST);
    bool checkButtons(bool _isHeld);            // returns true if there's any change in butons state
    bool checkEncoder();                        // returns true if there's a new encoder value
    void showBpm(long tempo, bool dot);
    void showNote(uint8_t note_value);
    void showNumber(long number);
    void setDot(bool);
    void displayValue(uint8_t mode, long value, uint8_t output = 0, bool dot = false);

    enum Modes: uint8_t{
        TEMPO         = 0,
        NOTE          = 1,
        SWING         = 2,
        PW            = 3
    };

    enum Outputs: uint8_t{
        MAIN          = 0,
        AUX1          = 1,
        AUX2          = 2,
        AUX3          = 3
    };

    enum Constants: uint8_t{
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
        COUNTER       = 12
    };

    uint8_t option;                     // the new button value (from Button::constants)
    int8_t encoderValue;                // signed - decrement or increment
    

    private:
    uint8_t dotMask;
    long lastTempo;
    long lastNote[4];
    long lastPW[4];
    long lastSwing[4];
    long lastDelay[4];
    uint8_t currentMode;
    uint8_t encoderData;
    uint8_t encoderSpeed;
    const uint16_t ENCODER_PERIOD = 150;
    MD_UISwitch_4017KM buttons;
    MD_UISwitch::keyResult_t key;
    MD_REncoder encoder;
    TM1637Display display;
    uint8_t displayData[4];
    int8_t adaptiveChange(uint8_t, uint8_t);
    void updateDisplay();
    uint8_t increment;
    void parseChars(char input[4]);
};
#endif