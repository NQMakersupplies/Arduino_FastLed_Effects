/*
  FastLed_Effects.h - Library for effects to use with FastLed.
  Created by Kurt Schoenhoff Kurt@nqmakersupplies.com.au 2016.
  Released into the public domain.
*/

#include "Arduino.h"
#include "FastLed.h"
#include "FastLed_Effects.h"


CRGB tempLeds1[1024];
CRGB tempLeds2[1024];
CRGB tempLeds3[1024];
CRGB tempLeds4[1024];

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

void FastLed_Effects::setSlowSpeed(uint8_t slowSpeed)
{
  _slowSpeed = slowSpeed;
}

void FastLed_Effects::setMedSpeed(uint8_t medSpeed)
{
  _medSpeed = medSpeed;
}

void FastLed_Effects::setFastSpeed(uint8_t fastSpeed)
{
  _fastSpeed = fastSpeed;
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

//EvenSidedGeoDotFadeColourWithRainbowSparkle
void FastLed_Effects::EvenSidedGeoDotFadeColourWithRainbowSparkle(CRGB leds[], uint16_t ledPosition, CRGB colour, int sides)
{
  //chop into sections

  uint16_t sectionSize = _numLeds / sides;
  ledPosition = map(ledPosition, 0, _numLeds - 1, 0, sectionSize - 1);
  
  uint16_t  i, j;
  int chanceOfGlitter = 5;
  
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( tempLeds1, sectionSize, 20);
  tempLeds1[ledPosition] += colour;


  fadeToBlackBy( tempLeds2, sectionSize , 5);
  

  if( random8() < chanceOfGlitter) {
    tempLeds2[ ledPosition ] += CHSV( _hue, 255, 192);
  }
  
  for ( i = 0; i < sides; i++)
  {
    for(j = 0; j < sectionSize; j++)
    {
      leds[j + (i * 79)] = tempLeds1[j] + tempLeds2[j];
    }
  }
  
}

//EvenSidedGeoDotFadeColourWithRainbowSparkle
void FastLed_Effects::EvenSidedGeoDotFadeBounceColourWithRainbowSparkle(CRGB leds[], uint16_t ledPosition, CRGB colour, int sides)
{
  //chop into sections

  uint16_t sectionSize = _numLeds / sides;
  ledPosition = map(ledPosition, 0, _numLeds - 1, 0, sectionSize - 1);
  
  uint16_t  i, j;
  int chanceOfGlitter = 10;
  
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( tempLeds1, sectionSize, 20);
  tempLeds1[ledPosition] += colour;

  fadeToBlackBy( tempLeds3, sectionSize, 20);
  tempLeds1[(sectionSize - 1) - ledPosition] += colour;

  //add glitter
  fadeToBlackBy( tempLeds2, sectionSize , 5);
  if( random8() < chanceOfGlitter) {
    tempLeds2[ ledPosition ] += CHSV( _hue, 255, 192);
  }

  fadeToBlackBy( tempLeds4, sectionSize , 5);
  if( random8() < chanceOfGlitter) {
    tempLeds4[(sectionSize - 1) -  ledPosition ] += CHSV( 254 -_hue, 255, 192);
  }
  
  for ( i = 0; i < sides; i++)
  {
    for(j = 0; j < sectionSize; j++)
    {
      leds[j + (i * sectionSize)] = tempLeds1[j] + tempLeds2[j] + tempLeds3[j] + tempLeds4[j] ;
    }
  } 
}

/*
//EvenSidedGeoDotFadeColourWithRainbowSparkle
void FastLed_Effects::EvenSidedGeoDotFadeBounceColourWithRainbowSparkleRotate(CRGB leds[], uint16_t ledPosition, CRGB colour, int sides)
{
  //chop into sections

  uint16_t sectionSize = _numLeds / sides;
  ledPosition = map(ledPosition, 0, _numLeds - 1, 0, sectionSize - 1);
  
  uint16_t  i, j;
  int chanceOfGlitter = 10;
  
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( tempLeds1, sectionSize, 20);
  tempLeds1[ledPosition] += colour;

  fadeToBlackBy( tempLeds3, sectionSize, 20);
  tempLeds1[(sectionSize - 1) - ledPosition] += colour;

  //add glitter
  fadeToBlackBy( tempLeds2, sectionSize , 5);
  if( random8() < chanceOfGlitter) {
    tempLeds2[ ledPosition ] += CHSV( _hue, 255, 192);
  }

  fadeToBlackBy( tempLeds4, sectionSize , 5);
  if( random8() < chanceOfGlitter) {
    tempLeds4[(sectionSize - 1) -  ledPosition ] += CHSV( 254 -_hue, 255, 192);
  }
  
  for ( i = 0; i < sides; i++)
  {
    for(j = 0; j < sectionSize; j++)
    {
      leds[j + (i * sectionSize)] = tempLeds1[j] + tempLeds2[j] + tempLeds3[j] + tempLeds4[j] ;
    }
  } 
}
*/

//// helper functions

/*
//Function to left rotate arr[] of size n by d
void leftRotate(CRGB arr[], uint16_t d, uint16_t n)
{
  uint16_t i;
  for (i = 0; i < d; i++)
    leftRotatebyOne(arr, n);
}
 
void leftRotatebyOne(CRGB arr[], uint16_t n)
{
  CRGB temp;
  uint16_t i;
  temp = arr[0];
  for (i = 0; i < n-1; i++)
     arr[i] = arr[i+1];
  arr[i] = temp;
}
*/




