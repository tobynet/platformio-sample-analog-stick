#ifndef __ANALOG_STICK_INCLUDED__
#define __ANALOG_STICK_INCLUDED__


class AnalogStick {
public:
    void setup(int pin_x, int pin_y, int pin_button);
    void calibrate();

    void update();


    bool is_center();
    bool is_position_changed();
    bool inline is_button_pressed() { return _is_button_pressed; }
    bool inline is_button_upped() { return _is_button_upped; }

    // After Serial.begin(9600); in initialization like a setup()
    void show_positions();

    
private:
    struct Position {
        int x;
        int y;
    };

    Position _old;
    Position _delta;
    Position _pos;
    Position _center;

    int _pin_y;
    int _pin_x;
    int _pin_button;

    int _button_count;
    bool _is_button_pressed;
    bool _is_button_upped;

    void button_check();
};


#endif