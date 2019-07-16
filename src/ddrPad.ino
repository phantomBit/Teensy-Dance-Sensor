// Built for Teensy 3.2
// Author: PhantomBit
// DDR Pad Project - Inspired by Promit's DanceForce Project

//Set to 1 to enable debugging Via Serial
const bool DEBUG = true;

//This is the LED pin for a Teensy 3.2
const int LedPin = 13;


class Pad {
private:

public:
    // Pin on the board
    int padPin;
    // analog check A#
    int padAnalogId;
    // Pin to trigger lights. set 0 to turn off.
    int lightPin;
    //The analog threshold value for triggering a button
    int threshold;
    // Which Joystick does this trigger
    int joystickButton;
    // was the pad triggered?
    bool triggered = false;
    // for debug
    int lastAnalogRead;

    Pad(int aPadPin, int aPadAnalogId, int aJoystickButton, int aThreshold = 150, int aLightPin = 0) {
        padPin = aPadPin;
        padAnalogId = aPadAnalogId;
        lightPin = aLightPin;
        threshold = aThreshold;
        joystickButton = aJoystickButton;
    }

    void init() {
        //The analog pins are configured with internal pull-up resistors, which makes for a very simple circuit
        pinMode(padPin, INPUT_PULLUP);

        if (lightPin != 0) {

        }
    }

    bool checkValue() {
        lastAnalogRead = analogRead(padPin);
        if (lastAnalogRead < threshold) {
            triggered = true;
            Joystick.button(joystickButton, 1);
        } else {
            triggered = false;
            Joystick.button(joystickButton, 0);
        }

        return triggered;
    }

    void triggerLight() {
        if (triggered) {

        }
    }
};


Pad padLeft(14, 0, 1, 150);
Pad padDown(15, 1, 2, 150);
Pad padUp(16, 2, 3, 150);
Pad padRight(17, 3, 4, 150);


void setup() {
    if (DEBUG) {
        Serial.begin(115200);
        while (!Serial) { ; // wait for serial port to connect. Needed for native USB port only
        }
    }

    pinMode(LedPin, OUTPUT);

    padLeft.init();
    padDown.init();
    padUp.init();
    padRight.init();
}

void loop() {
    bool pressed = false;

    if (padLeft.checkValue()) {
        pressed = true;
    }
    if (padDown.checkValue()) {
        pressed = true;
    }
    if (padUp.checkValue()) {
        pressed = true;
    }
    if (padRight.checkValue()) {
        pressed = true;
    }

    // turn on the Teensy board light if something was triggered
    if (pressed)
        digitalWrite(LedPin, HIGH);
    else
        digitalWrite(LedPin, LOW);


    if (DEBUG) {
        Serial.printf("Pins: %d %d %d %d %d\n", pressed, padLeft.lastAnalogRead, padDown.lastAnalogRead,
                      padUp.lastAnalogRead, padRight.lastAnalogRead);
        Serial.flush();
        delay(200);
    }

    //This limits the pad to run at 200 Hz. This version of the code does not debounce.
    delay(5);
}
