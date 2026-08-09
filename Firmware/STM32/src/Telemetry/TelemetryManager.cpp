#include "TelemetryManager.h"

void TelemetryManager::sendMessage(TelemetryPacket p)
{
     Serial.print((String)p.target + "," + (String)p.error + "," + (String)p.lastError + "," + (String)p.position + "," + (String)p.kp + "," + (String)p.ki + "," + (String)p.kd + "," + "," + (String)p.percentComplete + "," + (String)p.output + "\n");
}