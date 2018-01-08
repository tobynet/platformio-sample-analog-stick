#include <Arduino.h>
#include "analog_stick.h"

const int StickThreshold = 10;
const int StickCenterThreshold = 10;

const int centerX = 512;
const int centerY = centerX;
const int maxX = 1023;
const int maxY = maxX;

const int MaxButtonCount = 255;


void AnalogStick::setup(int pin_x, int pin_y, int pin_button) {
    _pin_x = pin_x;
    _pin_y = pin_y;
    _pin_button = pin_button;

    _is_button_pressed = false;
    _is_button_upped = false;

    pinMode(_pin_button, INPUT_PULLUP);

    calibrate();
}


void AnalogStick::calibrate() {
    _center.x = analogRead(_pin_x);
    _center.y = analogRead(_pin_y);
    _pos.x = _pos.y = 0;
    _old = _pos;
}


void AnalogStick::update() {
    _old = _pos;

    // アナログスティックのX,Y座標
    _pos.x = analogRead(_pin_x) - _center.x;
    _pos.y = analogRead(_pin_y) - _center.y;

    _delta.x = _pos.x - _old.x;
    _delta.y = _pos.y - _old.y;

    button_check();
}


bool AnalogStick::is_center() {
    return (abs(_pos.x) <= StickCenterThreshold) && (abs(_pos.y) <= StickCenterThreshold);
}


bool AnalogStick::is_position_changed() {
    return (StickThreshold <= abs(_delta.x)) || (StickThreshold <= abs(_delta.y));
}


void AnalogStick::button_check() {
    _is_button_pressed = false;
    _is_button_upped = false;
    
    // ボタン押下チェック
    if (digitalRead(_pin_button) == LOW) {
        if (_button_count == 0) {
            _is_button_pressed = true;
        }
        if (_button_count < MaxButtonCount) {
            _button_count++;
        }
    } else {
        if (0 < _button_count) {
            _is_button_upped = true;
        }
        _button_count = 0;
    }
}



void AnalogStick::show_positions() {
    Serial.print("AnalogStick(x,y): ");
    Serial.print(_pos.x); Serial.print(", "); Serial.print(_pos.y);
    Serial.print(" ("); Serial.print(_delta.x); Serial.print(", "); Serial.print(_delta.y); Serial.print(")");
    Serial.println("");
}

