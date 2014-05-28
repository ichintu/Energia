#include <SPI.h>
#include <AIR430BoostFCC.h>

#define ADDRESS_LOCAL    0x01


struct sPacket
{
  uint8_t from;           // Local node address that message originated from
  float tempC;
  float preshPA;
  int valLDR;
};

struct sPacket rxPacket;

void setup()
{
  Radio.begin(ADDRESS_LOCAL, CHANNEL_1, POWER_MAX);

  rxPacket.from = 0x0;
  rxPacket.tempC=0.00;
  rxPacket.preshPA=0.00;
  rxPacket.valLDR=0;
  Serial.begin(9600);
  Serial.println("*\t Starting Base Station \t*");
  pinMode(RED_LED, OUTPUT);       // Use red LED to display message reception
  digitalWrite(RED_LED, LOW);
}

void loop()
{
  if (Radio.receiverOn((unsigned char*)&rxPacket, sizeof(rxPacket), 1000) > 0)
  {
    digitalWrite(RED_LED, HIGH);
    Serial.print("FROM: ");
    Serial.print(rxPacket.from);  
    Serial.print(" Celsius: ");
    Serial.print(rxPacket.tempC);
    Serial.print(" Pressure: ");
    Serial.print(rxPacket.preshPA);   // display pressure in hPa
    Serial.print("hPa");
    Serial.print(" Light: ");
    Serial.println(rxPacket.valLDR);
    digitalWrite(RED_LED, LOW);
  }
}


