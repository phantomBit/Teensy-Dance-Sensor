// Built for Teensy 3.2
// Author: PhantomBit
// DDR Pad Project - Inspired by Promit's DanceForce Project

//Set to 1 to enable debugging Via Serial
const bool DEBUG = false;

//This is the LED pin for a Teensy 3.2
const int LedPin = 13;

/**
 * Arrow Button Class for keeping button information
 *
 * Usage:
 *    ArrowButton <variableName>(<sensorPin>, <joystickButton>, <threshold>, <lightPin>);
 *
 * Construct:
 * @param INT sensorPin
 *          the pin number the sensor is tied to. Must be analog read!
 *          3.2 Pins
 *              14-23. Recomended to use 14-19
 *
 * @param INT joystickButton
 *          the joystick button number you want pressed on activation
 *          Joystick Values
 *              1-32. Recomended to use 1-4
 *
 * @param INT threshold
 *          0-1000 to set sensetivity of the sensor
 *
 * @param INT lightPin
 *          the pin number the light is tied to. Must be PWM
 *          3.2 Pins
 *              3-6, 9-10, 20-23. Recomended to use 20-23
 */
class ArrowButton {
private:

public:
    int sensorPin;
    int lightPin;
    int threshold;
    int joystickButton;

    // was this button triggered during the loop?
    bool triggered = false;
    // for debug
    int lastAnalogRead;

    ArrowButton(int p_sensorPin, int p_joystickButton, int p_threshold = 150, int p_lightPin = 0) {
        sensorPin = p_sensorPin;
        joystickButton = p_joystickButton;
        threshold = p_threshold;
        lightPin = p_lightPin;
    }

    /**
     * Setup pins
     * TODO: Light Pin
     */
    void init() {
        //The analog pins are configured with internal pull-up resistors, which makes for a very simple circuit
        pinMode(sensorPin, INPUT_PULLUP);

        if (lightPin != 0) {

        }
    }

    /**
     * Checks the sensor state based on threshold value
     * TODO: add light pin
     * @return bool
     */
    bool sensorState() {
        lastAnalogRead = analogRead(sensorPin);
        if (lastAnalogRead < threshold) {
            triggered = true;
            Joystick.button(joystickButton, 1);
        } else {
            triggered = false;
            Joystick.button(joystickButton, 0);
        }

        return triggered;
    }
};

/**
 * Usage:
 *   ArrowButton <variableName>(<sensorPin>, <joystickButton>, <threshold>, <lightPin>);
 */
ArrowButton padLeft(14, 1, 150);
ArrowButton padDown(15, 2, 150);
ArrowButton padUp(16, 3, 150);
ArrowButton padRight(17, 4, 150);

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

    if (padLeft.sensorState()) {
        pressed = true;
    }
    if (padDown.sensorState()) {
        pressed = true;
    }
    if (padUp.sensorState()) {
        pressed = true;
    }
    if (padRight.sensorState()) {
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