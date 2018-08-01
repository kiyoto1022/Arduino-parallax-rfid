#include <SoftwareSerial.h>
#include <ParallaxRFID.h>
 ParallaxRFID RFIDclient(9,8);

void setup()
{
}

void loop()
{
  RFIDclient.writeRFID(4,1,1,1,1);
}
