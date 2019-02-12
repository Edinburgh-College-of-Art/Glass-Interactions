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
 * 3v       |     AREF
 * 
 */

void setup() 
{
  Serial.begin(115200);
  analogReference(EXTERNAL);
}

void loop() 
{
  int sensorValue = analogRead(A0); 
  Serial.println(sensorValue);
  delayMicroseconds(500);
}
