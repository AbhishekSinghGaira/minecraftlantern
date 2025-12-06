#include <Adafruit_NeoPixel.h> // NeoPixel library. Download if you don't have

#define PIXEL_PIN 3    // Input pin Neopixel is attached to
#define NUMPIXELS 16   // Number of neopixels in strip, change if using another quantity;

#define POT_PIN_R  A0  // Potentiometer on analog pin A0
#define POT_PIN_G  A1  // Potentiometer on analog pin A1
#define POT_PIN_B  A2  // Potentiometer on analog pin A2
#define POT_PIN_Br A3  // Potentiometer on analog pin A3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Initialize the variables
int redColor; 
int greenColor;
int blueColor;
int potValue;

void setup() {
  Serial.begin(9600);        // Initialize serial
  pixels.begin();            // Initialize the NeoPixel library.
  pixels.show();             // Update strip with new contents
  pixels.setBrightness(50);  // Set a initial brightness here
  
  rainbow(3);                // NeoPixel Test. Flowing rainbow cycle along the whole strip
};


void loop() {
  potValue   = analogRead(POT_PIN_R);          // Read the potentiometer value (0 to 1023)
  redColor   = map(potValue, 0, 1023, 0, 255); // Map the value to a brightness level (0 to 255)
  potValue   = analogRead(POT_PIN_G);          // Read the potentiometer value (0 to 1023) 
  greenColor = map(potValue, 0, 1023, 0, 255); // Map the value to a brightness level (0 to 255)
  potValue   = analogRead(POT_PIN_B);          // Read the potentiometer value (0 to 1023) 
  blueColor  = map(potValue, 0, 1023, 0, 255); // Map the value to a brightness level (0 to 255)
  
  //int potValue   = analogRead(POT_PIN_Br);         // Read the potentiometer value (0 to 1023) 
  //int brightness = map(potValue, 0, 1023, 0, 255); // Map the value to a brightness level (0 to 255)
  //pixels.setBrightness(brightness);                // Set the brightness for the entire strip

  // Prints the serial values of each potentiometer (Red, green, Blue). This is optional.
  Serial.print("r: "); Serial.println(redColor);
  Serial.print("g: "); Serial.println(greenColor);
  Serial.print("b: "); Serial.println(blueColor);
  //Serial.print("brightness: "); Serial.println(brightness);
  Serial.println("");
  
  for (int i=0; i < NUMPIXELS; i++) {
    // Pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
  };
  
  pixels.show();    // This sends the updated pixel color to the hardware.    
  delay(10);        // delay for a period of time (in milliseconds). Small delay for stability
};


//// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    pixels.rainbow(firstPixelHue);
    pixels.show(); // Update strip with new contents
    delay(wait);   // Pause for a moment
  };
};
