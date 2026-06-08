#include "TelemetryManager.h"

void TelemetryManager::sendMessage(TelemetryPacket p)
{
     Serial.println("SEND");
     Serial.print(p.toString());
}