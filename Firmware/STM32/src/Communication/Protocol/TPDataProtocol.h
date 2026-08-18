#ifndef TPDATAPROTOCOL
#define TPDATAPROTOCOL
#include <cstdint>
#include "Communication/CAN/CanFrame.h"
#include "Communication/CAN/Transport/Transport.h"
#include "Communication/CAN/SAEJ1939/J1939Identifier.h"
class TPDataProtocol
{
public:
    static CAN_Message create(const CAN_Message &, uint8_t);
};

#endif