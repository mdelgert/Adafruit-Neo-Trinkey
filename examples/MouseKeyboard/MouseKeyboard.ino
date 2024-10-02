#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include "Keyboard.h"
#include <Mouse.h>

// Create neopixel and touch objects
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

// Variables to track touch states
bool previousTouch1State = false;
bool previousTouch2State = false;
int touch1counter = 0;

// Timing values
unsigned long touch1StartTime = 0;
unsigned long touch2StartTime = 0;
const unsigned long holdThreshold = 500; // Hold time in milliseconds

// Message strings
const char hello1[] = "hello1";
const char hello2[] = "hello2";

// Blink and cycle timing
unsigned long blinkDelay = 500;        // Delay between LED blinks
unsigned long timer = 0;
unsigned long timerInterval = 60000;   // Interval for mouse move cycle

void setup() {
  Serial.begin(9600);
  
  // Setup the LED strip
  pixels.begin(); 
  pixels.setBrightness(20); 
  pixels.show(); 
  
  // Setup touch sensors
  if (!qt_1.begin())  
    Serial.println("Failed to begin qt on pin 1");
  if (!qt_2.begin())  
    Serial.println("Failed to begin qt on pin 2");
    
  Keyboard.begin();
}

void loop() {
  
  // Measure touch values
  uint16_t touch1 = qt_1.measure();
  uint16_t touch2 = qt_2.measure();
  bool Touch1State, Touch2State;

  // Handle touchpad 1
  if (touch1 > holdThreshold) {
    Touch1State = true;
    Keyboard.println(hello1);  // Send "hello1" when touch 1 is pressed
    Blink();
    delay(holdThreshold); 
  } else {
    Touch1State = false; 
  }

  // Handle touchpad 2
  if (touch2 > holdThreshold) {
    Touch2State = true;
    Keyboard.println(hello2);  // Send "hello2" when touch 2 is pressed
    Blink();
    delay(holdThreshold);
  } else {
    Touch2State = false;
  }
  
  // Trigger mouse movement periodically
  MoveCycle();  
}

void Blink()
{
  // Set color to green
  pixels.fill(0x00FF00);
  pixels.show();
  delay(blinkDelay); // Wait for blink delay

  // Turn off the LEDs
  pixels.fill(0x000000);
  pixels.show();
  delay(blinkDelay); // Wait for blink delay
}

void MoveCycle()
{
	if (millis() >= timer) {
		timer += timerInterval;  // Move mouse at the defined interval
		Mouse.move(1, 1, 0);
    Blink();  // Blink LEDs during mouse movement
	}
}
