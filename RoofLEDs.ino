#include "FastLED.h"
// Number of RGB LEDs in the strand
#define NUM_LEDS 500
// Arduino pin for data to LED strip
#define LED_Pin 8
// Arduino pin to toggle between Xmas and Ambient Lighting
#define XMAS_Pin 2
bool XMAS;
bool XMAS_OLD;
// Define the array of leds
CRGB leds[NUM_LEDS];



void setup()
{
  FastLED.addLeds<WS2812B, LED_Pin, BRG>(leds, NUM_LEDS);
  FastLED.setTemperature(0xFF8029);
  pinMode(XMAS_Pin, INPUT_PULLUP);
}

void loop() 
{
  //Read the Mode Pin from the Arduino
  XMAS_OLD = XMAS;
  XMAS = !digitalRead(XMAS_Pin);

  if(XMAS != XMAS_OLD)
  {
      FastLED.clear();
      FastLED.show();
  }
  

  if(XMAS == 0)
  {
    XMAS_Subroutine();
  }
  else
  {
    AMBIENT_Subroutine();
  }
  delay(5000);
}

void XMAS_Subroutine()
{

  for(int i = 0; i< NUM_LEDS; i=i+4) 
  {leds[i] = CRGB::White;
  FastLED.setBrightness(255);
  FastLED.show();
  delay(10);
  }

  for(int j = 2; j< NUM_LEDS; j=j+4) 
  {leds[j] = CRGB::Red;
  FastLED.show();
  delay(10);
  }
}

void AMBIENT_Subroutine()
{
  for(int i = 0; i< NUM_LEDS; i=i+1) 
  {leds[i] = CRGB::White;
  FastLED.setBrightness(99);
  FastLED.show();
  delay(10);
  }
}
