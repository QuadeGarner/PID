#ifndef TELEMETRYMANAGER
#define TELEMETRYMANAGER
#include "../Enums/CurrentStates.h"
#include "TelemetryPacket.h"
#include "Arduino.h"
class TelemetryManager
{
public:
    void sendMessage(TelemetryPacket);
};
#endif