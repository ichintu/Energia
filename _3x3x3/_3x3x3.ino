/*
  3 x 3 x 3
 Common Cathode
 */
int led[9];
int layer[3];
int c1, c2, c3;


void setup()
{
  led[0]=PB_5;
  led[1]=PB_0;
  led[2]=PB_1;
  led[3]=PE_4;
  led[4]=PE_5;
  led[5]=PB_4;
  led[6]=PA_5;
  led[7]=PA_6;
  led[8]=PA_7;

  layer[2]=PA_4;
  layer[1]=PA_3;
  layer[0]=PA_2;
  for(c1=0;c1<9;c1++)
  {
    pinMode(led[c1], OUTPUT);
  }

  for(c1=0;c1<3;c1++)
  {
    pinMode(layer[c1], OUTPUT);
    digitalWrite(layer[c1], LOW);
  }
}

void loop()
{
  /*
This loop will light up each individual LED 0 - 27
   */
  for(c1=0;c1<3;c1++){
    allOut();
    digitalWrite(layer[c1], LOW);
    for(c2=0;c2<9;c2++){
      clearPins();
      digitalWrite(led[c2], HIGH);
      delay(100);
    }
  }
  /* 
   This loop will light up each led vertically
   */
  allOut();
  for(c1=0;c1<9;c1++){
    clearPins();
    digitalWrite(led[c1], HIGH);
    for(c2=0;c2<3;c2++){
      clearRings();
      digitalWrite(layer[c2], LOW);
      delay(100);
    }
  }

  allOut();
  for(c1=0;c1<9;c1++){
    clearPins();
    digitalWrite(led[c1], HIGH);
    for(c2=0;c2<3;c2++){
      //clearRings();
      digitalWrite(layer[c2], LOW);
      delay(100);
    }
  }

  allOut();
  for(c1=0;c1<9;c1++){
    //clearPins();
    digitalWrite(led[c1], HIGH);
    for(c2=0;c2<3;c2++){
      clearRings();
      digitalWrite(layer[c2], LOW);
      delay(100);
    }
  }

  for(c1=0;c1<3;c1++){
    allOut();
    digitalWrite(layer[c1], LOW);
    for(c2=0;c2<9;c2++){
      clearPins();
      digitalWrite(led[c2], HIGH);
      delay(100);
    }
  }
allOut();
  for(c1=0;c1<3;c1++){
    clearRings();
    digitalWrite(layer[c1], LOW);
    for(c2=0;c2<9;c2++){
      clearPins();
      digitalWrite(led[c2], HIGH);
      delay(100);
    }
  }

}

void allOut()
{
  int i;
  for(i=0;i<9;i++)
  {
    digitalWrite(led[i], LOW);
    digitalWrite(layer[0], HIGH);
    digitalWrite(layer[1], HIGH);
    digitalWrite(layer[2], HIGH);    
  }
}

void clearPins()
{
  int i;
  for(i=0;i<9;i++)
  {
    digitalWrite(led[i], LOW);    
  }
}

void clearRings()
{
  digitalWrite(layer[0], HIGH);
  digitalWrite(layer[1], HIGH);
  digitalWrite(layer[2], HIGH); 
}










