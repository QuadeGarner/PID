#ifndef CAN_CODE_LIBRARY
#define CAN_CODE_LIBRARY
#include "../Communication/CAN/CanFrame.h"
namespace CanCodec
{
    void encodeInt32(Can_Frame &, uint8_t, int32_t);
    int32_t decodeInt32(const Can_Frame &, uint8_t);
    void encodeFloat(Can_Frame &, uint8_t, float, float scale = 1000.0f);
    float decodeFloat(const CAN_Frame &, uint8_t, float scale = 1000.0f);
}