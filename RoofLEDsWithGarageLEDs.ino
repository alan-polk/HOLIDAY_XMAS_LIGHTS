//Updated 11.19.2023 (New 24v Lights installed and debugged)

#include "FastLED.h"
// Number of RGB LEDs in each strands
#define NUM_LEDS_ROOF 350
#define NUM_LEDS_GARAGE 350
// Arduino pin for data to LED strips
#define LED_Pin_ROOF 8
#define LED_Pin_GARAGE 10
// Arduino pin to toggle between Xmas and Ambient Lighting
#define XMAS_Pin 2
bool XMAS;
bool XMAS_OLD;
bool CHANGED;
bool INIT;
// Define the array of leds
CRGB ledsROOF[NUM_LEDS_ROOF];
CRGB ledsGARAGE[NUM_LEDS_GARAGE];

void setup()
{
  FastLED.addLeds<WS2811, LED_Pin_ROOF, RGB>(ledsROOF, NUM_LEDS_ROOF);
  FastLED.setTemperature(0xFF8029); //Seems to give the best white, not too purple or yellow
  pinMode(XMAS_Pin, INPUT_PULLUP);
  ClearLEDs();
}

void loop() 
{
//Trap the Mode setting from last scan and then Read the Mode Pin from the Arduino
  XMAS_OLD = XMAS;
  XMAS = !digitalRead(XMAS_Pin);
//If the toggle switch changed, clear all the lights to prepare for new display
  if((XMAS != XMAS_OLD) or (INIT == 0))
  {
      CHANGED = 1;
      INIT = 1;
      ClearLEDs();
  }
  else
  {
    CHANGED = 0;
  }
 //If toggle switch is moved then check to set to XMAS or ambient, run the roof and garage subroutines  
  if (CHANGED == 1)
  {
    if(XMAS == 0)
    {
      INIT = 1;
      XMAS_ROOF_Subroutine();
      XMAS_GARAGE_Subroutine();
      FastLED.show();
    }
//If the toggle switch is set to AMBIENT, run the roof and garage subroutines
    else
    {
      INIT == 1;
      AMBIENT_ROOF_Subroutine();
      AMBIENT_GARAGE_Subroutine();  
      FastLED.show();
    }
  }
   delay(5000);
}

void ClearLEDs()
{
//Clear the roof LEDS
  FastLED.addLeds<WS2811, LED_Pin_ROOF, RGB>(ledsROOF, NUM_LEDS_ROOF);
  FastLED.setTemperature(0xFF8029);
  FastLED.clear();
//Clear the garage LEDS
  FastLED.addLeds<WS2811, LED_Pin_GARAGE, RGB>(ledsGARAGE, NUM_LEDS_GARAGE);
  FastLED.setTemperature(0xFF8029);
  FastLED.clear();

}
  
void XMAS_ROOF_Subroutine()
{
  FastLED.addLeds<WS2811, LED_Pin_ROOF, RGB>(ledsROOF, NUM_LEDS_ROOF);
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
  FastLED.addLeds<WS2811, LED_Pin_GARAGE, RGB>(ledsGARAGE, NUM_LEDS_GARAGE);
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
  FastLED.addLeds<WS2811, LED_Pin_ROOF, RGB>(ledsROOF, NUM_LEDS_ROOF);
  FastLED.setTemperature(0xFF8029);
    
  for(int i = 0; i< NUM_LEDS_ROOF; i=i+1) 
  {ledsROOF[i] = CRGB::White;
  FastLED.setBrightness(99);
  delay(10);
  }
}

void AMBIENT_GARAGE_Subroutine()
{
  FastLED.addLeds<WS2811, LED_Pin_GARAGE, RGB>(ledsGARAGE, NUM_LEDS_GARAGE);
  FastLED.setTemperature(0xFF8029);

  for(int i = 0; i< NUM_LEDS_GARAGE; i=i+99) 
  {ledsGARAGE[i] = CRGB::Black;
  delay(10);
  }
}
