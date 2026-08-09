#pragma once
#include "./Communication/CAN/Transport/Transport.h"
#include "./Librays/CanCodec.h"
#include "./Communication/CAN/CanProtocol.h"
class PIDCommandProtocol
{
public:
    static CAN_Message create(float, float);
    static float getTarget(const CAN_Message &);
    static float getPosition(const CAN_Message &);
};