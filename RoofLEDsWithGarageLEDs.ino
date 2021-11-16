#include "FastLED.h"
// Number of RGB LEDs in the strands
#define NUM_LEDS 500
// Arduino pin for data to LED strips
#define LED_Pin_ROOF 8
#define LED_Pin_GARAGE 6
// Arduino pin to toggle between Xmas and Ambient Lighting
#define XMAS_Pin 2
bool XMAS;
bool XMAS_OLD;
// Define the array of leds
CRGB leds[NUM_LEDS];


void setup()
{
  FastLED.addLeds<WS2812B, LED_Pin_ROOF, BRG>(leds, NUM_LEDS);
  FastLED.setTemperature(0xFF8029);
  pinMode(XMAS_Pin, INPUT_PULLUP);
}

void loop() 
{
  //Read the Mode Pin from the Arduino
  XMAS_OLD = XMAS;
  XMAS = !digitalRead(XMAS_Pin);
 //If the toggle switch changed, clear all the lights to prepare for new display
  if(XMAS != XMAS_OLD)
  {
      FastLED.clear();
      FastLED.show();
  }
  
  if(XMAS == 0)
  {
    XMAS_ROOF_Subroutine();
    XMAS_GARAGE_Subroutine();
  }
  else
  {
    AMBIENT_ROOF_Subroutine();
    AMBIENT_GARAGE_Subroutine();
  }
  delay(5000);
}

void XMAS_ROOF_Subroutine()
{
  FastLED.addLeds<WS2812B, LED_Pin_ROOF, BRG>(leds, NUM_LEDS);
  FastLED.setTemperature(0xFF8029);

  for(int i = 0; i< NUM_LEDS; i=i+4) 
  {leds[i] = CRGB::Green;
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

void XMAS_GARAGE_Subroutine()
{
  FastLED.addLeds<WS2812B, LED_Pin_GARAGE, BRG>(leds, NUM_LEDS);
  FastLED.setTemperature(0xFF8029);

  for(int i = 0; i< NUM_LEDS; i=i+4) 
  {leds[i] = CRGB::Green;
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

void AMBIENT_ROOF_Subroutine()
{
  FastLED.addLeds<WS2812B, LED_Pin_ROOF, BRG>(leds, NUM_LEDS);
  FastLED.setTemperature(0xFF8029);

  FastLED.clear();
  FastLED.show();
    
  for(int i = 0; i< NUM_LEDS; i=i+1) 
  {leds[i] = CRGB::White;
  FastLED.setBrightness(99);
  FastLED.show();
  delay(10);
  }
}

void AMBIENT_GARAGE_Subroutine()
{
  FastLED.addLeds<WS2812B, LED_Pin_GARAGE, BRG>(leds, NUM_LEDS);
  FastLED.setTemperature(0xFF8029);

  FastLED.clear();
  FastLED.show();
}
