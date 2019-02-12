/*
 * Read SPW2430 Mic
 * 
 * Connections
 * 
 * Mic      |     Arduino
 * ______________________
 * Vin      |     5V
 * GND      |     GND
 * DC       |     A0
 * 
 */

void setup() 
{
  Serial.begin(115200);
  analogReference(INTERNAL);
}

void loop() 
{
  int sensorValue = analogRead(A0); 
  Serial.println(sensorValue);
  delayMicroseconds(500);
}
