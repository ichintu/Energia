#include <SPI.h>
#include <AIR430BoostFCC.h>


#define ADDRESS_LOCAL    0x01

struct sPacket
{
  uint8_t from;           // Local node address that message originated from
  float x;
  int y;
};

struct sPacket rxPacket;


void setup()
{
  Radio.begin(ADDRESS_LOCAL, CHANNEL_1, POWER_MAX);
  rxPacket.from = 0;
  rxPacket.x=0.00;
  rxPacket.y=0;
  Serial.begin(9600);
  Serial.println("Starting HUB...");
}

void loop()
{
  if (Radio.receiverOn((unsigned char*)&rxPacket, sizeof(rxPacket), 1000) > 0)
  {
    Serial.print("FROM: ");
    Serial.print(rxPacket.from);
    Serial.print(" X: ");
    Serial.print(rxPacket.x, 2);
    Serial.print(" Y: ");
    Serial.println(rxPacket.y, DEC);
  }
}


