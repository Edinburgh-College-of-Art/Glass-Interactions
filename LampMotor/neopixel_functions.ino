//==========================================================================================
/**
   This function cycles through most of the available colours when given a value between 0 and 255
   i.e. colourWheel(0) will give a pretty similar colour to colourWheel(255)
*/
uint32_t colourWheel(byte WheelPos)
{
  uint32_t newColour = 0;
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    newColour = Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if (WheelPos < 170)
  {
    WheelPos -= 85;
    newColour = Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else
  {
    WheelPos -= 170;
    newColour = Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  return newColour;
}

//==========================================================================

void fadeUp()
{
  brightness += fadeStepSize;
  if (brightness >= 255)
  {
    brightness = 255;
    lightsAreOn = true;
  }
  uint32_t b = Adafruit_NeoPixel::Color(brightness, brightness, brightness);
  pixelRing.fill(b, 0, pixelRing.numPixels());
  pixelRing.show();

}

//==========================================================================

void fadeDown()
{
  if (brightness >= fadeStepSize)
  {
    brightness -= fadeStepSize;
  }
  else
  {
    brightness = 0;
    lightsAreOn = false;
  }

  uint32_t b = Adafruit_NeoPixel::Color(brightness, brightness, brightness);
  pixelRing.fill(b, 0, pixelRing.numPixels());
  pixelRing.show();
}

//==========================================================================

void turnDownLights()
{
  while (lightsAreOn)
  {
    fadeDown();
  }
}
void turnDownLights(unsigned long currentTime)
{
  //  static unsigned long previousTime = 0;
  //  if (currentTime - previousTime  >= fadeIntervalTime)
  //  {
  //    fadeDown();
  //    previousTime = currentTime;
  //  }
}

//==========================================================================

void turnUpLights()
{
  while (!lightsAreOn)
  {
    fadeUp();
  }
}
void turnUpLights(unsigned long currentTime)
{
  //  static unsigned long previousTime = 0;
  //  if (currentTime - previousTime  >= fadeIntervalTime)
  //  {
  //    fadeUp();
  //    previousTime = currentTime;
  //  }
}
//==========================================================================

void updateRingColour()
{
  for (int i = 0; i < 256; i++)
  {
    pixelRing.fill(colourWheel(i), 0, pixelRing.numPixels());
    pixelRing.show();
    delay(delayBetweenColourChanges);
  }
}
