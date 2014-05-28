#include <stdio.h>
#include <string.h>

char inBuffer[12];
char* tok;
boolean strComplete=false;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  serialMon();
  if(strComplete)
  {
    Serial.print("Data Received:\t");
    tok=strtok(inBuffer, ",");
    while(tok != NULL)
    {
      Serial.println(tok);
      tok=strtok(NULL, ",");
    }

    strComplete=false;
  }
  if(!strComplete)
  {

  }

}

void serialMon() {
  int c=0;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inBuffer[c] = inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      strComplete = true;
      return;
    }
    c++ ;
    if (c>11) {
      Serial.println("ERROR: Invalid Syntax");
      strComplete = false;
      return;
    }
  }
}



