/*

*/
//--------------------------------------------------------------------------------
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
//--------------------------------------------------------------------------------
#include <Adafruit_NeoPixel.h>
//--------------------------------------------------------------------------------
#define PIN            5
#define NUMPIXELS      144
//--------------------------------------------------------------------------------
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second
//--------------------------------------------------------------------------------
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
//--------------------------------------------------------------------------------
// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin
//--------------------------------------------------------------------------------
Adafruit_VS1053_FilePlayer musicPlayer =
  // create breakout-example object!
  //Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
//--------------------------------------------------------------------------------
void setup()
{
  pixels.begin(); // This initializes the NeoPixel library.

  Serial.begin(9600);

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(51, 0, 0)); // Cherry Red color.
  }

  pixels.show(); // This sends the updated pixel color to the hardware.

  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin())
  {
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }

  // list files
  printDirectory(SD.open("/"), 0);

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20, 20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  //  // Play one file, don't return until complete
  //  Serial.println(F("Playing track 001"));
  //  musicPlayer.playFullFile("/01.mp3");
  // Play another file in the background, REQUIRES interrupts!
  //  Serial.println(F("Playing track 002"));
  //  musicPlayer.startPlayingFile("/track002.mp3");
}
//--------------------------------------------------------------------------------
void loop()
{

  Serial.println(F("Playing track 001")); // Play one file, don't return until complete
  musicPlayer.playFullFile("/01.mp3");

  if (musicPlayer.stopped()) // File is playing in the background
  {
    Serial.println("Done playing music");
  }

  readSerialInput();

  delay(100);
}
