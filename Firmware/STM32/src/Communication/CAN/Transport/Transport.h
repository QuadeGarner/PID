#ifndef TRANSPORT
#define TRANSPORT
#include <cstdint>
#include "../SAEJ1939/J1939Identifier.h"
struct CAN_Message
{
    // J1939Identifier
    J1939Identifier identifier;
    uint8_t length;
    uint8_t payload[1785];
};
#endif