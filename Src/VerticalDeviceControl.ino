#include "Motor.h"
#include "Clip.h"
#include "ToFSensor.h"
#include "Indicator.h"
#include "LimitSwitch.h"

#ifdef ESP32
#include "WirelessInterface.h"
WirelessInterface wireless;
#endif

// Pin definitions
const int MOTOR_DIR_PIN  = 2;
const int MOTOR_EN_PIN   = 3;
const int GREEN_LED_PIN  = 4;
const int RED_LED_PIN    = 5;
const int BUZZER_PIN     = 6;
const int TOP_SWITCH_PIN = 7;
const int CLIP_PIN       = 8;

// Distance thresholds (meters)
const float START_DISTANCE        = 1.3;
const float INTERMEDIATE_DISTANCE = 1.8;
const float TOP_DISTANCE          = 2.2;

// Objects
Motor motor(MOTOR_DIR_PIN, MOTOR_EN_PIN);
Indicator green(GREEN_LED_PIN), red(RED_LED_PIN), buzzer(BUZZER_PIN);
LimitSwitch topSwitch(TOP_SWITCH_PIN);
Clip clip(CLIP_PIN);
ToFSensor tof;

enum State { MOVE_UP_TOP, WAIT_TOP, MOVE_DOWN_START, MOVE_UP_INTERMEDIATE, HOLD };
State currentState = MOVE_UP_TOP;

unsigned long waitTimer = 0;

void setup() {
    Serial.begin(115200);
    
    motor.begin();
    green.begin(); red.begin(); buzzer.begin();
    topSwitch.begin();
    clip.begin();
    tof.begin();

#ifdef ESP32
    wireless.begin();
#endif

    green.on(); red.off(); buzzer.off();
}

void loop() {
    // ---------------------------
    // WIRED SEQUENCE
    // ---------------------------
    switch(currentState) {
        case MOVE_UP_TOP:
            motor.up();
            if(topSwitch.isPressed()) {
                motor.stop();
                currentState = WAIT_TOP;
                waitTimer = millis();
                green.off(); red.on(); buzzer.on();
            }
            break;

        case WAIT_TOP:
            if(millis() - waitTimer >= 15000) {
                red.off(); buzzer.off(); green.on();
                currentState = MOVE_DOWN_START;
            }
            break;

        case MOVE_DOWN_START:
            motor.down();
            if(tof.distanceMeters() <= START_DISTANCE) {
                motor.stop();
                green.off(); red.on(); buzzer.on();
                waitTimer = millis();
                currentState = MOVE_UP_INTERMEDIATE;
            }
            break;

        case MOVE_UP_INTERMEDIATE:
            motor.up();
            static bool clipReleased = false;
            if(tof.distanceMeters() >= INTERMEDIATE_DISTANCE && !clipReleased) {
                clip.release();
                clipReleased = true;
            }
            if(tof.distanceMeters() >= TOP_DISTANCE) {
                motor.stop();
                green.off(); red.on(); buzzer.on();
                waitTimer = millis();
                currentState = HOLD;
            }
            break;

        case HOLD:
            motor.stop();
            break;
    }

    // ---------------------------
    // WIRELESS CONTROL (ESP32 only)
    // ---------------------------
#ifdef ESP32
    if(wireless.available()) {
        String cmd = wireless.readCommand();
        if(cmd == "MOVE_UP") motor.up();
        else if(cmd == "MOVE_DOWN") motor.down();
        else if(cmd == "STOP") motor.stop();
        else if(cmd == "RELEASE_CLIP") clip.release();
    }

    wireless.sendStatus("Height:" + String(tof.distanceMeters()));
#endif

    delay(10); // small non-blocking delay
}