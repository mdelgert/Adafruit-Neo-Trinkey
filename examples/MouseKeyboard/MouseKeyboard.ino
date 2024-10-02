#include "Config.h"
//#include "ConfigSecure.h"

// Initialize NeoPixel and touch objects
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

// Initialize variables
bool previousTouch1State = false;
bool previousTouch2State = false;
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);

  // Setup NeoPixel
  pixels.begin(); 
  pixels.setBrightness(20); 
  pixels.show(); 

  // Setup touch sensors
  if (!qt_1.begin()) Serial.println("Failed to initialize qt on pin 1");
  if (!qt_2.begin()) Serial.println("Failed to initialize qt on pin 2");

  // Initialize the keyboard
  Keyboard.begin();
}

void loop() {
  // Measure touch values
  uint16_t touch1 = qt_1.measure();
  uint16_t touch2 = qt_2.measure();

  // Check touchpad states and send corresponding messages
  handleTouch(touch1, previousTouch1State, hello1);
  handleTouch(touch2, previousTouch2State, hello2);

  // Handle periodic mouse movement
  MoveCycle();  
}

// Function to handle touchpad state and keyboard messages
void handleTouch(uint16_t touchValue, bool &previousState, const char* message) {
  if (touchValue > holdThreshold) {
    if (!previousState) {
      // If touched and was not previously touched
      Keyboard.println(message);
      Blink();
    }
    previousState = true;
  } else {
    previousState = false;  // Reset state if not touched
  }
}

// Function to blink the NeoPixels
void Blink() {
  pixels.fill(0x00FF00);  // Set pixels to green
  pixels.show();
  delay(blinkDelay);      // Wait

  pixels.fill(0x000000);  // Turn off pixels
  pixels.show();
  delay(blinkDelay);      // Wait
}

// Function to handle periodic mouse movement
void MoveCycle() {
  if (millis() >= timer) {
    timer += timerInterval;
    Mouse.move(1, 1, 0);  // Move mouse slightly
    Blink();              // Blink LEDs
  }
}
