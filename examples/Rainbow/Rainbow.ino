//**Tools** -> **Board** -> **Adafruit SAMD Boards** -> **Adafruit Neo Trinkey M0** (https://adafruit.github.io/arduino-board-index/package_adafruit_index.json)

#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Create the two touch pads on pins 1 and 2:
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

int16_t neo_brightness = 20; // initialize with 20 brightness (out of 255)

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  strip.begin();
  strip.setBrightness(neo_brightness);
  strip.show(); // Initialize all pixels to 'off'

  if (! qt_1.begin())  
    Serial.println("Failed to begin qt on pin 1");
  if (! qt_2.begin())  
    Serial.println("Failed to begin qt on pin 2");
}

void loop() {
  uint16_t i, j;

  for(j=0; j<256; j++) { // cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(10);

    // measure the captouches
    uint16_t touch1 = qt_1.measure();
    uint16_t touch2 = qt_2.measure();

    // If the first pad is touched, reduce brightness
    if (touch1 > 500) {
      // subtract 1 from brightness but dont go below 0
      neo_brightness = max(0, neo_brightness-1);
      Serial.print("New brightness: "); Serial.println(neo_brightness);
      strip.setBrightness(neo_brightness);
    }

    // If the second pad is touched, increase brightness
    if (touch2 > 500) {
      // add 1 to brightness but dont go above 255
      neo_brightness = min(255, neo_brightness+1);      
      Serial.print("New brightness: "); Serial.println(neo_brightness);
      strip.setBrightness(neo_brightness);
    }

    // don't print touch data constantly, only every 10 runs  
    if (j % 10 == 0) {
      Serial.print("QT 1: "); Serial.print(touch1);
      Serial.print("\t\tQT 2: "); Serial.println(touch2);
    }
  }

}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}