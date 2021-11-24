#include "FastLED.h"
// Number of RGB LEDs in each strands
#define NUM_LEDS_ROOF 350
#define NUM_LEDS_GARAGE 150
// Arduino pin for data to LED strips
#define LED_Pin_ROOF 8
#define LED_Pin_GARAGE 9
// Arduino pin to toggle between Xmas and Ambient Lighting
#define XMAS_Pin 2
bool XMAS;
bool XMAS_OLD;
// Define the array of leds
CRGB ledsROOF[NUM_LEDS_ROOF];
CRGB ledsGARAGE[NUM_LEDS_GARAGE];

void setup()
{
  FastLED.addLeds<WS2812B, LED_Pin_ROOF, BRG>(ledsROOF, NUM_LEDS_ROOF);
  FastLED.setTemperature(0xFF8029); //Seems to give the best white, not too purple or yellow
  pinMode(XMAS_Pin, INPUT_PULLUP);
  ClearLEDs();
}

void loop() 
{
//Trap the Mode setting from last scan adn then Read the Mode Pin from the Arduino
  XMAS_OLD = XMAS;
  XMAS = !digitalRead(XMAS_Pin);
//If the toggle switch changed, clear all the lights to prepare for new display
  if(XMAS != XMAS_OLD)
  {
      ClearLEDs();
  }
//If toggle switch is set to XMAS, run the roof and garage subroutines  
  if(XMAS == 0)
  {
    XMAS_ROOF_Subroutine();
    XMAS_GARAGE_Subroutine();
  }
//If the toggle switch is set to AMBIENT, run the roof and garage subroutines
  else
  {
    AMBIENT_ROOF_Subroutine();
    AMBIENT_GARAGE_Subroutine();  
  }

  FastLED.show();
  delay(5000);
}

void ClearLEDs()
{
//Clear the roof LEDS
  FastLED.addLeds<WS2812B, LED_Pin_ROOF, BRG>(ledsROOF, NUM_LEDS_ROOF);
  FastLED.setTemperature(0xFF8029);
  FastLED.clear();
//Clear the garage LEDS
  FastLED.addLeds<WS2812B, LED_Pin_GARAGE, BRG>(ledsGARAGE, NUM_LEDS_GARAGE);
  FastLED.setTemperature(0xFF8029);
  FastLED.clear();

}
  
void XMAS_ROOF_Subroutine()
{
  FastLED.addLeds<WS2812B, LED_Pin_ROOF, BRG>(ledsROOF, NUM_LEDS_ROOF);
  FastLED.setTemperature(0xFF8029);

  for(int i = 0; i< NUM_LEDS_ROOF; i=i+4) 
  {ledsROOF[i] = CRGB::Green;
  FastLED.setBrightness(255);
  delay(10);
  }

  for(int j = 2; j< NUM_LEDS_ROOF; j=j+4) 
  {ledsROOF[j] = CRGB::Red;
  delay(10);
  }
}

void XMAS_GARAGE_Subroutine()
{
  FastLED.addLeds<WS2812B, LED_Pin_GARAGE, BRG>(ledsGARAGE, NUM_LEDS_GARAGE);
  FastLED.setTemperature(0xFF8029);

  for(int i = 0; i< NUM_LEDS_GARAGE; i=i+4) 
  {ledsGARAGE[i] = CRGB::Green;
  FastLED.setBrightness(255);
  delay(10);
  }

  for(int j = 2; j< NUM_LEDS_GARAGE; j=j+4) 
  {ledsGARAGE[j] = CRGB::Red;
  delay(10);
  }
}

void AMBIENT_ROOF_Subroutine()
{
  FastLED.addLeds<WS2812B, LED_Pin_ROOF, BRG>(ledsROOF, NUM_LEDS_ROOF);
  FastLED.setTemperature(0xFF8029);
    
  for(int i = 0; i< NUM_LEDS_ROOF; i=i+1) 
  {ledsROOF[i] = CRGB::White;
  FastLED.setBrightness(99);
  delay(10);
  }
}

void AMBIENT_GARAGE_Subroutine()
{
  FastLED.addLeds<WS2812B, LED_Pin_GARAGE, BRG>(ledsGARAGE, NUM_LEDS_GARAGE);
  FastLED.setTemperature(0xFF8029);

  for(int i = 0; i< NUM_LEDS_GARAGE; i=i+99) 
  {ledsGARAGE[i] = CRGB::Black;
  delay(10);
  }
}
