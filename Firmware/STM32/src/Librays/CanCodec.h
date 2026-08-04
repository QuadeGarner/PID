#ifndef CAN_CODE_LIBRARY
#define CAN_CODE_LIBRARY
#include "../Communication/CAN/Transport.h"
namespace CanCodec
{
    void encodeInt32(CAN_Message &, uint8_t, int32_t);
    int32_t decodeInt32(const CAN_Message &, uint8_t);
    void encodeFloat(CAN_Message &, uint8_t, float, float scale = 1000.0f);
    float decodeFloat(const CAN_Message &, uint8_t, float scale = 1000.0f);
    void encodeInt16(CAN_Message &, uint8_t, int16_t);
    int16_t decodeInt16(const CAN_message &, uint16_t);

}