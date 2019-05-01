//--------------------------------------------------------------------------------
void pixelSetup()
{
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  // CLEAR LEDS
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB( 51, 0, 0);
  FastLED.show();
}
//--------------------------------------------------------------------------------
CRGB Scroll(int pos)
{
  CRGB color (0, 0, 0);
  if (pos < 85)
  {
    color.g = 0;
    color.r = ((float)pos / 85.0f) * 255.0f;
    color.b = 255 - color.r;
  } else if (pos < 170)
  {
    color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
    color.r = 255 - color.g;
    color.b = 0;
  } else if (pos < 256) {
    color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
    color.g = 255 - color.b;
    color.r = 1;
  }
  return color;
}
//--------------------------------------------------------------------------------
void updateColorWheel()
{
  k = k - wheel_speed; // SPEED OF COLOR WHEEL
  if (k < 0) // RESET COLOR WHEEL
    k = 255;

  // REMOVE LEDs
  decay_check++;
  if (decay_check > decay)
  {
    decay_check = 0;
    if (react > 0)
      react--;
  }
}
//--------------------------------------------------------------------------------
void rainbow()
{
  for (int j = 0; j < numStrips; ++j)
  {
    for (int i = 0; i < pixPerStrip; ++i)
    {
      int p = ((j % 2) == 0) ? (i + (j * pixPerStrip)) : ((j * pixPerStrip) + (pixPerStrip - 1) - i);
      leds[p] = (i < react) ? Scroll((i * 256 / 50 + k) % 256) : CRGB(0, 0, 0);
    }
  }
  FastLED.show();
}
