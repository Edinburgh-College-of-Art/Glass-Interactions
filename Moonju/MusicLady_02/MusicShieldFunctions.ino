void setuoMusicShield()
{
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
  printDirectory(SD.open("/"), 0); // list files 
}

void printDirectory(File dir, int numTabs)/// File listing helper
{
  while (true)
  {
    File entry =  dir.openNextFile();
    if (! entry)
    {
      // no more files
      //Serial.println("**nomorefiles**");
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++)
    {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory())
    {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    }
    else
    {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}


void readSerialInput()
{
  if (Serial.available())
  {
    char c = Serial.read();

    switch (c)
    {
      case 's':
        musicPlayer.stopPlaying();
        break;
      case 'p':
        if (! musicPlayer.paused()) 
        {
          Serial.println("Paused");
          musicPlayer.pausePlaying(true);
        } 
        else 
        {
          Serial.println("Resumed");
          musicPlayer.pausePlaying(false);
        }
        break;
    }
  }
}
