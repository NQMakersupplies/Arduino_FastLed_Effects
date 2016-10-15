/*
  FastLed_Effects.cpp - Library for flashing FastLed_Effects code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "FastLed.h"
#include "FastLed_Effects.h"


CRGB tempLeds1[1024];
CRGB tempLeds2[1024];

FastLed_Effects::FastLed_Effects(int num_Leds)
{
  _numLeds = num_Leds;
}

int FastLed_Effects::getNumLeds()
{
  return (_numLeds);
}

void FastLed_Effects::setNumLeds(int num_Leds)
{
  _numLeds = num_Leds;
}

void FastLed_Effects::setHue(uint8_t hue)
{
  _hue = hue;
}

/////////////////////////////////
///         Effects           ///

void FastLed_Effects::fillRainbow(CRGB leds[])
{
  fill_rainbow( leds, _numLeds, _hue, 7);
}


void FastLed_Effects::addGlitter(CRGB leds[])
{
  addGlitter(leds, 80);
}

void FastLed_Effects::addGlitter(CRGB leds[], fract8 chanceOfGlitter)
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(_numLeds) ] += CRGB::White;
  }
}

void FastLed_Effects::confetti(CRGB leds[])
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, _numLeds, 10);
  int pos = random16(_numLeds);
  leds[pos] += CHSV( _hue + random8(64), 200, 255);
}

void FastLed_Effects::sinelon(CRGB leds[])
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, _numLeds, 20);
  int pos = beatsin16(13,0,_numLeds);
  leds[pos] += CHSV( _hue, 255, 192);
}

void FastLed_Effects::bpm(CRGB leds[])
{
  bpm(leds, 62);
}

void FastLed_Effects::bpm(CRGB leds[], uint8_t beatsPerMinute)
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( beatsPerMinute, 64, 255);
  for( int i = 0; i < _numLeds; i++) { //9948
    leds[i] = ColorFromPalette(palette, _hue+(i*2), beat-_hue+(i*10));
  }
}

void FastLed_Effects::juggle(CRGB leds[])
{
    // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, _numLeds, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,_numLeds)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void FastLed_Effects::dotFade(CRGB leds[])
{
  dotFade(leds, _hue/4);
}

void FastLed_Effects::dotFade(CRGB leds[], uint16_t ledPosition)
{
  dotFadeHue(leds, _hue/4, _hue);
}

void FastLed_Effects::dotFadeHue(CRGB leds[], uint16_t ledPosition, uint8_t hue)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, _numLeds, 20);
  leds[ledPosition] += CHSV( _hue, 255, 192);
}

void FastLed_Effects::dotFadeColour(CRGB leds[], uint16_t ledPosition, CRGB colour)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, _numLeds, 20);
  leds[ledPosition] += colour;
}

void FastLed_Effects::dotFadeColourWithSparkle(CRGB leds[], uint16_t ledPosition, CRGB colour)
{
  int chanceOfGlitter = 5, i;
  
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( tempLeds1, _numLeds, 20);
  tempLeds1[ledPosition] += colour;


  fadeToBlackBy( tempLeds2, _numLeds, 5);
  

  if( random8() < chanceOfGlitter) {
    tempLeds2[ ledPosition ] += CRGB::Green;
  }
  

  for(i = 0; i < _numLeds; i++)
  {
    leds[i] = tempLeds1[i] + tempLeds2[i];
  }
  
}

void FastLed_Effects::dotFadeColourWithRainbowSparkle(CRGB leds[], uint16_t ledPosition, CRGB colour)
{
  int chanceOfGlitter = 5, i;
  
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( tempLeds1, _numLeds, 20);
  tempLeds1[ledPosition] += colour;


  fadeToBlackBy( tempLeds2, _numLeds, 5);
  

  if( random8() < chanceOfGlitter) {
    tempLeds2[ ledPosition ] += CHSV( _hue, 255, 192);
  }
  

  for(i = 0; i < _numLeds; i++)
  {
    leds[i] = tempLeds1[i] + tempLeds2[i];
  }
  
}


