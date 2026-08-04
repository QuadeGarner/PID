#ifndef TRANSPORT
#define TRANSPORT
#include <cstdint>
struct CAN_Message
{
    uint32_t messageID;
    uint16_t length;
    uint8_t payload[1785];
};
#endif