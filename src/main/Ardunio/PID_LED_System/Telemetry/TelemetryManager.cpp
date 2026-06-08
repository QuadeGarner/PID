#include "TELEMETRYMANGER.h"

void TelemetryManger::sendMessage(TelemetryPacket p){
     Serial.print(p.toString());
}