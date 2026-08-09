#pragma once
#include "../src/Communication/CAN/Transport/Transport.h"
#include "./Communication/CAN/CanProtocol.h"
#include "./Librays/CanCodec.h"
// #include "./Communication/CAN/Transport/Transport.h"
class PIDUpdateProtocol
{
public:
    static CAN_Message create(float, float, float);
    static float getKP(const CAN_Message &);
    static float getKI(const CAN_Message &);
    static float getKD(const CAN_Message &);
};