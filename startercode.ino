// Add the line http://arduino.esp8266.com/stable/package_esp8266com_index.json 
// under File>Preferences>Additional Boards Manager URLs
// Tools > Boards Manager > search 'ESP8266' and install the library
// Sketch > Include Library > Manage Libraries > search 'Neopixel' and install the Adafruit Neopixel 

#include <Adafruit_NeoPixel.h> // required for display
#include <ESP8266WiFi.h> // required to use the pins on the Wemos Mini

//#define NUMPIXELS 12 // the number of pixels we are using
//#define PIN D6 // the pin we are using for the Neopixel
//#define INPUT_PIN A0 // Analog input pin.

//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //the neopixel object

// This function takes in a RGB value and sets all the colors
/*
void setAllPixels(int r, int g, int b){
  for (int j = 0; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, pixels.Color(r, g, b));
    }
    pixels.show();
}
*/


// This function takes a pixel number, and a RGB value and sets the colors
/*
void setPixel(int j, int r, int g, int b){
  pixels.setPixelColor(j, pixels.Color(r, g, b));
  pixels.show();  
}
*/


void setup() {
  // put your setup code here, to run once:
  // pinMode(D1,OUTPUT);
  // pinMode(A0,INPUT);
  // pinMode(INPUT_PIN,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // delay(1000);
}
