//////////////////////////////////////////////////////////////////
//Released under the MIT License - Please reuse change and share
//Simple code for the TMP102, simply prints temperature via serial
//i2c Pins PD_0 (SCL) PD_1 (SDA)
//////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <BMP085_t.h>

int tmp102Address = 0x48;
int ldr = PD_2;
BMP085<3> PSensor;

void setup(){
  pinMode(ldr, INPUT);
  Serial.begin(9600);
  Wire.begin();
  PSensor.begin();
}

void loop(){
  PSensor.refresh();                  // read current sensor data
  delay(5);
  float celsius = getTemperature();
  delay(5);
  PSensor.calculate();
  delay(5);
  Serial.print("Celsius: ");
  Serial.print(celsius);
  Serial.print(" Pressure: ");
  Serial.print((PSensor.pressure+50)/100);   // display pressure in hPa
  Serial.print("hPa");
  Serial.print(" Light: ");
  Serial.println(chkLight(), DEC);
  delay(5000);
}

float getTemperature(){
  Wire.requestFrom(tmp102Address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  return celsius;
}

int chkLight()
{
  int x=analogRead(ldr);
  return x; 
}



