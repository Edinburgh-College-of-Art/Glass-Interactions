//--------------------------------------------------------------------------------
/* 
 *   Arduino Music Visualizer 0.2
 *   This music visualizer works off of analog input from a 3.5mm headphone jack
 *   Just touch jumper wire from A0 to tip of 3.5mm headphone jack
 *   The code is dynamic and can handle variable amounts of LEDs
 *   as long as you adjust NUM_LEDS according to the amount of LEDs you are using
 *   
 */
//--------------------------------------------------------------------------------
#include <FastLED.h>
//--------------------------------------------------------------------------------
// LED LIGHTING SETUP
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100
//--------------------------------------------------------------------------------
const int LED_PIN     = 5;
const int numStrips   = 8;
const int pixPerStrip = 18;
const int NUM_LEDS    = pixPerStrip * numStrips;
CRGB leds[NUM_LEDS];
//--------------------------------------------------------------------------------
int audio = A0;
//--------------------------------------------------------------------------------
// STANDARD VISUALIZER VARIABLES
int loop_max = 0;
int k = 255; // COLOR WHEEL POSITION
int decay = 0; // HOW MANY MS BEFORE ONE LIGHT DECAY
int decay_check = 0;
long pre_react = 0; // NEW SPIKE CONVERSION
long react = 0; // NUMBER OF LEDs BEING LIT
long post_react = 0; // OLD SPIKE CONVERSION
//--------------------------------------------------------------------------------
// RAINBOW WAVE SETTINGS
int wheel_speed = 3;
//--------------------------------------------------------------------------------
void setup()
{  
  pixelSetup();
  Serial.begin(115200);
  pinMode(audio, INPUT);
  Serial.println("\nListening...");
}
//--------------------------------------------------------------------------------
void loop()
{
  int audio_input = analogRead(audio); // ADD x2 HERE FOR MORE SENSITIVITY

  if (audio_input > 0)
  {
    pre_react = ((long)pixPerStrip * (long)audio_input) / 1023L; // TRANSLATE AUDIO LEVEL TO NUMBER OF LEDs

    if (pre_react > react) // ONLY ADJUST LEVEL OF LED IF LEVEL HIGHER THAN CURRENT LEVEL
      react = pre_react;

    Serial.print(audio_input);
    Serial.print(" -> ");
    Serial.println(pre_react);
  }

  rainbow(); // APPLY COLOR

  updateColorWheel();
}
