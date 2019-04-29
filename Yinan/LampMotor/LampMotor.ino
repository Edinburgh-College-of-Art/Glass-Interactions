/*
     Arduino Motor Control
     by Yinan Chu

     Pin Out
     _______

     Ultrasound | Arduino
     VCC        | 5V
     TRIG       | 4
     ECHO       | 5
     GND        | GND

     NeoPixels  | Arduino
     5V         | 5V
     Data       | 9
     GND        | GND

*/
//====================================================================
#include <Stepper.h>
#include <Ultrasonic.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
//====================================================================
const int stepsPerRev = 200;
const int totalSteps = ((stepsPerRev * 25) / 2) - 75;
boolean extended = false;
Stepper myStepper(stepsPerRev, 12, 13);
int currentPosition;
//====================================================================
const int trig = 4;
const int echo = 5;
Ultrasonic ultrasonic(trig, echo);
int threshold = 30;
//==========================================================================================
int pixelNumber  = 20;
int pixelDataPin =  10;
int delayBetweenColourChanges = 100;
//==========================================================================================
uint16_t pixelType = NEO_GRB + NEO_KHZ800; // type should always be this for your NeoPixels
uint16_t brightness = 255;
uint8_t fadeStepSize = 1;
bool lightsAreOn = false;
Adafruit_NeoPixel pixelRing = Adafruit_NeoPixel(pixelNumber, pixelDataPin, pixelType);
//==========================================================================================
void setup()
{
  Serial.begin(9600);
  setupMotor();
  setupUltrasound();

  pixelRing.begin();
  pixelRing.clear();
  pixelRing.show();
}
//====================================================================
void loop()
{
  int distance = ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(distance);

  if (distance < threshold && !extended)
  {
    turnUpLights();
    extend();
    delay(2000);
  }
  else if (distance > threshold && extended)
  {    
    retract();
    turnDownLights();
    delay(2000);
  }
  else
  {
    delay(200);
  }
}
//====================================================================
