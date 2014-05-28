#include <Wire.h>
#include <BMP085_t.h>
#include <SPI.h>
#include <AIR430BoostFCC.h>

#define ADDRESS_LOCAL    0x02
#define ADDRESS_REMOTE   0x01

int tmp102Address = 0x48;
int ldr = PD_2;
BMP085<3> PSensor;

struct sPacket
{
  uint8_t from;           // Local node address that message originated from
  float tempC;
  float preshPA;
  int valLDR;
};

struct sPacket txPacket;

void setup(){
  pinMode(ldr, INPUT);
  Radio.begin(ADDRESS_LOCAL, CHANNEL_1, POWER_MAX);
  txPacket.from = ADDRESS_LOCAL;
  txPacket.tempC=0.00;
  txPacket.preshPA=0.00;
  txPacket.valLDR=0;
  Serial.begin(9600);
  Wire.begin();
  PSensor.begin();
  pinMode(GREEN_LED, OUTPUT);
}


void loop(){
  PSensor.refresh();                  // read current sensor data
  delay(5);
  txPacket.tempC = getTemperature();
  delay(5);
  Serial.print("Celsius: ");
  Serial.print(txPacket.tempC, 2);
  PSensor.calculate();
  delay(5);
  txPacket.preshPA = (PSensor.pressure+50)/100;
  txPacket.valLDR = chkLight();
  Serial.print(" Pressure: ");
  Serial.print(txPacket.preshPA, 2);   // display pressure in hPa
  Serial.print("hPa");
  Serial.print(" Light: ");
  Serial.println(txPacket.valLDR, DEC);
  digitalWrite(GREEN_LED, HIGH);
  Serial.print(sizeof(txPacket));
  Serial.println(" Bytes Sent");  
  Radio.transmit(ADDRESS_REMOTE, (unsigned char*)&txPacket, sizeof(txPacket));
  delay(5);
  digitalWrite(GREEN_LED, LOW);
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






