#include "FastLED.h"
#include "FastLed_Effects.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN  5
#define CLOCK_PIN 4
#define LED_TYPE    APA102
#define COLOR_ORDER BGR
#define NUM_LEDS    312//leds third corner 234 + 235 //leds second corner = 156 and 157// led first corner =78 and 79 //total = 390
CRGB leds[NUM_LEDS];

//CRGB myLeds[NUM_LEDS];

//CRGB tempLeds1[NUM_LEDS];
//CRGB tempLeds2[NUM_LEDS];

FastLed_Effects ledEffects(NUM_LEDS);

#define BRIGHTNESS          400
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(0x80B0FF);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; ledEffects.setHue(gHue);} // slowly cycle the "base color" through the rainbow
  
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow()
{
  ledEffects.fillRainbow(leds);
}

void rainbowWithGlitter() 
{
  ledEffects.fillRainbow(leds);
  ledEffects.addGlitter(leds, 80);
}


void confetti() 
{
 ledEffects.confetti(leds);
}

void sinelon()
{
  ledEffects.sinelon(leds);
}

void bpm()
{
  ledEffects.bpm(leds);
}

void juggle() 
{
  ledEffects.juggle(leds);
}

void dotFade() 
{
  ledEffects.dotFadeColourWithRainbowSparkle(leds, gHue/4, CRGB::White);
}

