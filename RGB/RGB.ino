void setup(){
  pinMode(PF_1, OUTPUT);
  pinMode(PF_2, OUTPUT);
  pinMode(PF_3, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int r=0,g=0,b=0;
  for(r=1;r<254;r = r+10){
    for(g=1;g<254;g=g+10){
      for(b=1;b<254;b = b+10){
        analogWrite(PF_1,r);
        analogWrite(PF_3,g);
        analogWrite(PF_2,b);
        Serial.print(r);
        Serial.print(",");
        Serial.print(g);
        Serial.print(",");
        Serial.println(b);
        delay(250);
      }
    }
  }
}


