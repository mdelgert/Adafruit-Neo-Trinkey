#ifndef CONFIG_H
#define CONFIG_H

#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include "Keyboard.h"
#include <Mouse.h>

// Constants for the setup
const unsigned long holdThreshold = 500;     // Hold time in milliseconds
const unsigned long blinkDelay = 500;        // Delay for LED blink
const unsigned long timerInterval = 60000;   // Interval for mouse movement
const char hello1[] = "hello1";              // Message for touchpad 1
const char hello2[] = "hello2";              // Message for touchpad 2

// Create NeoPixel and touch objects
extern Adafruit_NeoPixel pixels;
extern Adafruit_FreeTouch qt_1;
extern Adafruit_FreeTouch qt_2;

// Variables to track touch states and timers
extern bool previousTouch1State;
extern bool previousTouch2State;
extern unsigned long timer;

// Function prototypes
void handleTouch(uint16_t touchValue, bool &previousState, const char* message);
void Blink();
void MoveCycle();

#endif // CONFIG_H
