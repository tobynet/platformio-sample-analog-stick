#include <Arduino.h>
//#include "sample_led.h"
#include "analog_stick.h"

const int XPin = A0;
const int YPin = A1;
const int ButtonPin = 15;

const int DelayTime = 1000 / 100;

#define print_val(x) Serial.print(#x ": "); Serial.println(x);

AnalogStick stick;

void print_debug() {
    Serial.print("  "); print_val(XPin);
    Serial.print("  "); print_val(YPin);
}

void setup() {
    stick.setup(XPin, YPin, ButtonPin);

    Serial.begin(9600);
}



void loop() {
    // 更新処理
    stick.update();

    //// 変化していた場合に値を表示
    //if (isXYChanged(deltaX, deltaY)) {

    // 中心からずれていた場合に、値を表示
    if (!stick.is_center()) {
        stick.show_positions();
    }

    // ボタン押下チェック
    if (stick.is_button_pressed()) {
        Serial.print("Button: PRESSED! ");
        stick.show_positions();
        print_debug();
    }
    // ボタン離したチェック
    if (stick.is_button_upped()) {
        Serial.print("Button: upped! ");
        stick.show_positions();
    }

    delay(DelayTime);
}