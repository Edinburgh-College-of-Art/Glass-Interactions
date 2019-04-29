/*

*/
//--------------------------------------------------------------------------------
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Adafruit_NeoPixel.h>
//--------------------------------------------------------------------------------
#define PIN            5
#define NUMPIXELS      144
//--------------------------------------------------------------------------------
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second
//--------------------------------------------------------------------------------
#define BREAKOUT_RESET  9    // VS1053 reset pin (output)
#define BREAKOUT_CS     10   // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8    // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1     // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
//--------------------------------------------------------------------------------
// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin
//--------------------------------------------------------------------------------
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
//--------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);

  pixels.begin();
  pixels.fill(pixels.Color(51, 0, 0), 0, NUMPIXELS);
  pixels.show();

  setuoMusicShield();
  musicPlayer.setVolume(20, 20); // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
}
//--------------------------------------------------------------------------------
void loop()
{
  Serial.println(F("Playing track 001")); // Play one file, don't return until complete
  musicPlayer.playFullFile("/01.mp3");
  readSerialInput();
  delay(100);
}
