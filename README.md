# Arduino_FastLed_Effects
Library for FastLed Effects.

Mission:
========
To create a library of effects for use with fast led.


Interface Description for Effects:
==============================================

constructor:
------------
As a minumum to keep maximum portability each effect will be able to use the following constructor:

FastLed_Effects effects(Num_Leds);


Methods:
--------


effects.getNumLeds()
Returns _numLeds

effects.setNumLeds(int Num_Leds)
used to set internal _numLeds

effects.setGlobalHue(uint8_t hue)
used to set internal _hue



Effect Methods:
---------------


    void fillRainbow(CRGB leds[]);

    void addGlitter(CRGB leds[]);
    void addGlitter(CRGB leds[], fract8 chanceOfGlitter);
    
    void confetti(CRGB leds[]); 

    void sinelon(CRGB leds[]); 

    void bpm(CRGB leds[]);
    void bpm(CRGB leds[], uint8_t beatsPerMinute);

    void juggle(CRGB leds[]);