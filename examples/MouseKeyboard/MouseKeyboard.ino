#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include "Keyboard.h"
#include <Mouse.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

bool previousTouch1State = false;
bool previousTouch2State = false;
int touch1counter = 0;

unsigned long touch1StartTime = 0;
unsigned long touch2StartTime = 0;
const unsigned long holdThreshold = 500;

unsigned long timer = 0;
unsigned long blinkDelay = 500;
unsigned long timerInterval = 60000;

void setup() {
  Serial.begin(9600);
  
  pixels.begin(); 
  pixels.setBrightness(20); 
  pixels.show(); 
  
  if (!qt_1.begin())  
    Serial.println("Failed to begin qt on pin 1");
  if (!qt_2.begin())  
    Serial.println("Failed to begin qt on pin 2");
    
  Keyboard.begin();
}

void loop() {
  
  uint16_t touch1 = qt_1.measure();
  uint16_t touch2 = qt_2.measure();
  
  bool Touch1State, Touch2State;

  Serial.print("QT 1: "); Serial.print(touch1);
  Serial.print("\t\tQT 2: "); Serial.println(touch2);

  if (touch1 > holdThreshold) {
    Touch1State = true;
    //Keyboard.println("hello1");
    Blink();
    delay(holdThreshold); 
  } else {
    Touch1State = false; 
  }

  if (touch2 > holdThreshold) {
    Touch2State = true;
    //Keyboard.println("hello2");
    Blink();
    delay(holdThreshold);
  } else {
    Touch2State = false;
  }
  
  /*
    if (touch1 > 500) {
    Touch1State = true;
  } else {
    Touch1State = false; 
  }

  if (touch2 > 500) {
    Touch2State = true;
  } else {
    Touch2State = false;
  }
  
  // Touchpad 1: Detect press or hold
  if (Touch1State && !previousTouch1State) {
    touch1StartTime = millis();  // Start counting time when touch 1 is first pressed
  }

  if (!Touch1State && previousTouch1State) {
    // On release, check if it was a hold or tap
    if (millis() - touch1StartTime > holdThreshold) {
      Blink();
      Keyboard.println("hello1");
    } 
  }

  // Touchpad 2: Detect press or hold
  if (Touch2State && !previousTouch2State) {
    touch2StartTime = millis();  // Start counting time when touch 2 is first pressed
  }

  if (!Touch2State && previousTouch2State) {
    // On release, check if it was a hold or tap
    if (millis() - touch2StartTime > holdThreshold) {
      Blink();
      Keyboard.println("hello2");
    } 
  }

  previousTouch1State = Touch1State;
  previousTouch2State = Touch2State;
  */
  
  MoveCycle();
  //delay(10);  
}

void Blink()
{
  // set color
  pixels.fill(0x00FF00);
  pixels.show();
  delay(blinkDelay); // wait half a second

  // turn off
  pixels.fill(0x000000);
  pixels.show();
  delay(blinkDelay);
}

void MoveCycle()
{
	if (millis() >= timer)
	{
		timer += timerInterval;
		Mouse.move(1, 1, 0);
    Blink();
	}
}
