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

#define FASTLED_ALLOW_INTERRUPTS 0 
#define DATA_PIN  5
#define CLOCK_PIN 4
#define LED_TYPE    APA102
#define COLOR_ORDER BGR
#define NUM_LEDS    390//Leds fourth corner 312//leds third corner 234 + 235 //leds second corner = 156 and 157// led first corner =78 and 79 //total = 390
CRGB leds[NUM_LEDS];

#define NUM_SIDES 5

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
SimplePatternList gPatterns = { GeoDotFadeEndBounceRotate2};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
int gHue = 0; // rotating "base color" used by many of the patterns
uint8_t slowSpeed = 0;
uint8_t medSpeed = 0;
uint8_t fastSpeed = 0;
  
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
  EVERY_N_MILLISECONDS( 20 ) {slowSpeed++; /*ledEffects.setSlowSpeed(slowSpeed);*/} 
  EVERY_N_MILLISECONDS( 7 ) {medSpeed++; /*ledEffects.setMedSpeed(medSpeed);*/} 
  EVERY_N_MILLISECONDS( 1 ) {fastSpeed++; /*ledEffects.setFastSpeed(fastSpeed);*/} 
  
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
  uint16_t dotPosition = map(gHue,0,254,0,NUM_LEDS - 1);
  ledEffects.dotFadeColourWithRainbowSparkle(leds, dotPosition, CRGB::White);
}

void GeoDotFade() 
{
  uint16_t dotPosition = map(fastSpeed,0,254,0,NUM_LEDS - 1);
  
  ledEffects.EvenSidedGeoDotFadeBounceColourWithRainbowSparkle(leds, dotPosition, CRGB::White, NUM_SIDES);
}

void GeoDotFadeTimes2() 
{
  uint16_t dotPosition = map(fastSpeed,0,254,0,NUM_LEDS - 1);
  
  ledEffects.EvenSidedGeoDotFadeBounceColourWithRainbowSparkle(leds, dotPosition, CRGB::White, NUM_SIDES * 2);
}

void GeoDotFadeTimes4() 
{
  uint16_t dotPosition = map(fastSpeed,0,254,0,NUM_LEDS - 1);
  
  ledEffects.EvenSidedGeoDotFadeBounceColourWithRainbowSparkle(leds, dotPosition, CRGB::White, NUM_SIDES * 4);
}

void GeoDotFadeEndBounce() 
{
  uint16_t dotPosition = map(fastSpeed,0,254,0,NUM_LEDS - 1);
  
  ledEffects.EvenSidedGeoDotFadeBounceColourWithRainbowSparkle(leds, dotPosition, CRGB::White, 1);
}

void GeoDotFadeEndBounceRotate() 
{
  uint16_t dotPosition = map(fastSpeed,0,254,0,NUM_LEDS - 1);

  uint16_t rotate = map(slowSpeed,0,254,0,NUM_LEDS - 1);
  
  ledEffects.EvenSidedGeoDotFadeBounceColourWithRainbowSparkle(leds, dotPosition, CRGB::White, NUM_SIDES * 4);

  leftRotate(leds, rotate, NUM_LEDS);
  
}

void GeoDotFadeEndBounceRotate2() 
{
  uint16_t dotPosition = map(fastSpeed,0,254,0,NUM_LEDS - 1);

  uint16_t rotate = map(slowSpeed,0,254,0,NUM_LEDS - 1);
  
  ledEffects.EvenSidedGeoDotFadeBounceColourWithRainbowSparkle(leds, dotPosition, CRGB::White, NUM_SIDES * 4);

  leftRotate(leds, rotate, NUM_LEDS);
  
}

void pointer_shift(CRGB *a, int n) {
   int i;
   for (i = 0; i != n - 1; i++) {
      *(a+i) = *(a+i+1);
   }
}

/*Function to left rotate arr[] of size n by d*/
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



