#ifndef TELEMETRYMANAGER
#define TELEMETRYMANAGER
#include "CURRENTSTATE.h"
#include "TELEMETRYPACKET.h"
class TelemetryManager{
    public:
        void sendMessage(TelemetryPacket);
};
#endif