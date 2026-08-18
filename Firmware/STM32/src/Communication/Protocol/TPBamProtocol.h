#ifndef TPBAMPROTOCOL
#define TPBAMPROTOCOL
#include "../CAN/Transport/Transport.h"
#include "../src/Librays/CanCodec.h"
#include "../CAN/CanProtocol.h"
#include "Communication/CAN/SAEJ1939/J1939Identifier.h"
class TPBamProtocol
{
public:
    static CAN_Message create(const CAN_Message &);
    static int32_t getOriginalMessageId(const CAN_Message &);
    static int16_t getFrameCount(const CAN_Message &);
    static int16_t getOriginalMessageLength(const CAN_Message &);
    // static int16_t computeFrameCount(CAN_Message);
};
#endif