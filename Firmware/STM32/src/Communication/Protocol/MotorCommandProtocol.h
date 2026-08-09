#ifndef MOTORCOMMANDPROTOCOL
#define MOTORCOMMANDPROTOCOL
#include "../src/Communication/CAN/Transport/Transport.h"
class MotorCommandProtocol
{
public:
    static CAN_Message create(float power);
    static float getPower(const CAN_Message &);
};
#endif