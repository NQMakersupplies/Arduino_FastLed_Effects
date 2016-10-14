# Arduino_FastLed_Effects
Library for FastLed Effects.

Mission:
========
To create a library of effects for use with fast led.


Interface Description for Effects that create:
==============================================

constructor:
------------
As a minumum to keep maximum portability each effect will be able to use the following constructor:

Effect effect(Num_Leds);


Methods:
--------

effect.getLeds()
Return a CRGB array of size Num-Leds, if required use default parameters if the effect needs some more information.
It is also suggested to use overloading to keep this method as the only one required for returning led array state.

effect.getNumLeds()
Returns _Num_Leds

effect.setNumLeds(int Num_Leds)
used to set internal _Num_Leds

effect.setGlobalHue(uint8_t gHue)
used to set internal _globalHue



Interface Description for Effects that modify and existing CRGB array:
==============================================

constructor:
------------
As a minumum to keep maximum portability each effect will be able to use the following constructor:

Effect effect(Num_Leds);


Methods:
--------

effect.getLeds(CRGB[] ledsToModify)
Return a CRGB array of size Num-Leds, if required use default parameters if the effect needs some more information.
It is also suggested to use overloading to keep this method as the only one required for returning led array state.

effect.getNumLeds()
Returns _Num_Leds

effect.setNumLeds(int Num_Leds)
used to set internal _Num_Leds

effect.setGlobalHue(uint8_t gHue)
used to set internal _globalHue

