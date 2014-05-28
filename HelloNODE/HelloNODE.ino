#include <SPI.h>
#include <AIR430BoostFCC.h>

#define ADDRESS_LOCAL    0x02
#define ADDRESS_REMOTE   0x01

struct sPacket
{
  uint8_t from;           // Local node address that message originated from
  float tempC;
  float preshPA;
  int valLDR;
};


struct sPacket txPacket;

void setup()
{
  Radio.begin(ADDRESS_LOCAL, CHANNEL_1, POWER_MAX);
  txPacket.from = ADDRESS_LOCAL;
  txPacket.tempC=0.00;
  txPacket.preshPA=0.00;
  txPacket.valLDR=0;
  Serial.begin(9600);
}

void loop()
{
  txPacket.tempC+=1;
  txPacket.preshPA+=1;
  txPacket.valLDR+=1;
  Radio.transmit(ADDRESS_REMOTE, (unsigned char*)&txPacket, sizeof(txPacket));
  delay(1000);
}

