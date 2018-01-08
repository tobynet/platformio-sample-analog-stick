#include <Arduino.h>
#include "sample_led.h"

// ref. https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/example-1-blinkies
#define LEDPIN LED_BUILTIN_RX

const int shortDelay = 200;

void led_on() {
    digitalWrite(LEDPIN, LOW);
    // or RXLED1;

    TXLED0; // turns the TX LED off
}

void led_off() {
    digitalWrite(LEDPIN, HIGH);
    // or RXLED0;

    TXLED1; // turns the TX LED on
}

void sample_led_setup() {
    pinMode(LEDPIN, OUTPUT); //LED on Model A  or Pro
    TXLED0;
}

void sample_led_loop() {
    for (auto x = 0; x < 10; x++){
        led_on();
        delay(shortDelay);
        led_off();
        delay(shortDelay);
    }

    led_on();
    TXLED1;
    delay(1000);

    led_off();
    TXLED0;
    delay(1000);               // wait for a second
}