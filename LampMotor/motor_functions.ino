void extend()
{
  myStepper.step(totalSteps);
  extended = true;
}

void retract()
{
  myStepper.step(-totalSteps );
  extended = false;
}

void setupMotor()
{
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(11, HIGH);
  myStepper.setSpeed(160);
//  currentPosition = EEPROM.read(0) * 10; // Read current position
}

void setupUltrasound()
{
  ultrasonic.read();
  delay(100);
}
