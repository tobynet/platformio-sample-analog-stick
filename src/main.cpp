#include <Arduino.h>
#include "sample_led.h"

const int XPin = A0;
const int YPin = A1;
const int ButtonPin = 15;

const int DelayTime = 1000 / 120;
const int StickThreshold = 10;
const int StickCenterThreshold = 10;


const int centerX = 512;
const int centerY = centerX;
const int maxX = 1023;
const int maxY = maxX;

int oldX;
int oldY;
int deltaX;
int deltaY;
int initialCenterX;
int initialCenterY;


void calibulateStick() {
    initialCenterX = analogRead(XPin);
    initialCenterY = analogRead(YPin);
    oldX = analogRead(XPin) - initialCenterX;
    oldY = analogRead(YPin) - initialCenterY;
}

void setup() {
    pinMode(ButtonPin, INPUT_PULLUP);

    calibulateStick();

    Serial.begin(9600);
}

void updateDelta(int x, int y, int oldX, int oldY) {
    deltaX = x - oldX;
    deltaY = y - oldY;
}

bool isXYChanged(int deltaX, int deltaY, int threshold = StickThreshold) {
    return (threshold <= abs(deltaX)) || (threshold <= abs(deltaY));
}

bool isCenter(int x, int y, int threshold = StickCenterThreshold) {
    return (abs(x) <= threshold) && (abs(y) <= threshold);
}

void showXY(int x, int y) {
    Serial.print("Stick(x,y): ");
    Serial.print(x); Serial.print(", "); Serial.print(y);
    Serial.print(" ("); Serial.print(deltaX); Serial.print(", "); Serial.print(deltaY); Serial.print(")");
    Serial.println("");
}

void loop() {
    static int buttonCount = 0;

    // ジョイスティックのX,Y座標
    int x = analogRead(XPin) - initialCenterX;
    int y = analogRead(YPin) - initialCenterY;

    // 変化を取得
    updateDelta(x, y, oldX, oldY);

    //// 変化していた場合に値を表示
    //if (isXYChanged(deltaX, deltaY)) {
    // 中心からずれていた場合に、値を表示
    if (!isCenter(x, y)) {
        showXY(x, y);
    }
    oldX = x; oldY = y;


    // ボタン押下チェック
    if (digitalRead(ButtonPin) == LOW) {
        if (buttonCount == 0) {
            Serial.print("Button: PRESSED! ");
            showXY(x, y);
        }
        if (buttonCount < 255) {
            buttonCount++;
        }
    } else {
        if (0 < buttonCount) {
            Serial.print("Button: up. ");
            showXY(x, y);
        }
        buttonCount = 0;
    }

    delay(DelayTime);
}