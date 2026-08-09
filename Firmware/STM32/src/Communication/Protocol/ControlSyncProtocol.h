#pragma once
#include "../CAN/Transport/Transport.h"
#include "../CAN/CanProtocol.h"
#include "../src/Librays/CanCodec.h"
#include <stdint.h>
class ControlSyncProtocol
{
public:
    static CAN_Message create(float, uint32_t);
    static float getTime(const CAN_Message &);
    static uint32_t getTickCount(const CAN_Message &);
};