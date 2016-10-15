/*
  FastLed_Effects.h - Library for effects to use with FastLed.
  Created by Kurt Schoenhoff Kurt@nqmakersupplies.com.au 2016.
  Released into the public domain.
*/
#ifndef FastLed_Effects_h
#define FastLed_Effects_h

#include "Arduino.h"
#include "FastLed.h"

//template for creating effect
class FastLed_Effects
{
  public:
    FastLed_Effects(int num_Leds);
    
    
    int getNumLeds();
    void setNumLeds(int num_Leds);
    void setHue(uint8_t hue);

    void fillRainbow(CRGB leds[]);

    void addGlitter(CRGB leds[]);
    void addGlitter(CRGB leds[], fract8 chanceOfGlitter);
    
    void confetti(CRGB leds[]); 

    void sinelon(CRGB leds[]); 

    void bpm(CRGB leds[]);
    void bpm(CRGB leds[], uint8_t beatsPerMinute);

    void juggle(CRGB leds[]);

  private:
    int _numLeds;
    uint8_t _hue;
};

#endif
