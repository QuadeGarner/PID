#ifndef PIDSTATUSPROTOCOL
#define PIDSTATUSPROTOCOL
#include "../src/Communication/CAN/Transport/Transport.h"
class PidStatusProtocol
{
public:
    static CAN_Message create(float output, float error, float lastError);
    static float getOutput(const CAN_Message &);
    static float getError(const CAN_Message &);
    static float getLastError(const CAN_Message &);
};
#endif