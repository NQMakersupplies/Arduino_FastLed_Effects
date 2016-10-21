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
    void setHue(uint8_t _hue);
    void setSlowSpeed(uint8_t _slowSpeed);
    void setMedSpeed(uint8_t _medSpeed);
    void setFastSpeed(uint8_t _fastSpeed);

    void fillRainbow(CRGB leds[]);

    void addGlitter(CRGB leds[]);
    void addGlitter(CRGB leds[], fract8 chanceOfGlitter);
    
    void confetti(CRGB leds[]); 

    void sinelon(CRGB leds[]); 

    void bpm(CRGB leds[]);
    void bpm(CRGB leds[], uint8_t beatsPerMinute);

    void juggle(CRGB leds[]);

    void dotFade(CRGB leds[]);
    void dotFade(CRGB leds[], uint16_t ledPosition); 
    void dotFadeHue(CRGB leds[], uint16_t ledPosition, uint8_t hue );
    void dotFadeColour(CRGB leds[], uint16_t ledPosition, CRGB colour );

    void dotFadeColourWithSparkle(CRGB leds[], uint16_t ledPosition, CRGB colour );

    void dotFadeColourWithRainbowSparkle(CRGB leds[], uint16_t ledPosition, CRGB colour );

    void EvenSidedGeoDotFadeColourWithRainbowSparkle(CRGB leds[], uint16_t ledPosition, CRGB colour, int sides );

    void EvenSidedGeoDotFadeBounceColourWithRainbowSparkle(CRGB leds[], uint16_t ledPosition, CRGB colour, int sides );

  private:
    int _numLeds;
    uint8_t _hue;
    uint8_t _slowSpeed;
    uint8_t _medSpeed;
    uint8_t _fastSpeed;
};

#endif
