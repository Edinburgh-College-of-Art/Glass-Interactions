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

    switch ()
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
