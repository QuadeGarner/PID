#include "CanCodec.h"
namespace CanCodec
{
    // Store a signed 32-bit int into four bytes
    void encodeInt32(CAN_Message &message, uint8_t startByte, int32_t value)
    {
        if (startByte + sizeof(int32_t) >= message.length)
        {
            // will need to change to return something meaningful
            return;
        }

        message.payload[startByte] = (value >> 24) & 0xFF;
        message.payload[startByte + 1] = (value >> 16) & 0xFF;
        message.payload[startByte + 2] = (value >> 8) & 0xFF;
        message.payload[startByte + 3] = value & 0xFF;
    }
    // Decodes a 32 bit int from 4 bytes
    int32_t decodeInt32(const CAN_Message &message, uint8_t startByte)
    {
        if (startByte + 3 >= message.length)
        {
            return -1;
        }
        return (static_cast<int32_t>(message.payload[startByte]) << 24) |
               (static_cast<int32_t>(message.payload[startByte + 1]) << 16) |
               (static_cast<int32_t>(message.payload[startByte + 2]) << 8) |
               (static_cast<int32_t>(message.payload[startByte + 3]));
    }
    // Encodes a float by scaling and storing it as an int32
    void encodeFloat(CAN_Message &message, uint8_t startByte, float value, float scale)
    {
        int32_t intValue = static_cast<int32_t>(value * scale);
        encodeInt32(message, startByte, intValue);
    }
    // decodes a scaled int32 back into a float
    float decodeFloat(const CAN_Message &message, uint8_t startByte, float scale)
    {
        int32_t value = decodeInt32(message, startByte);
        return static_cast<float>(value) / scale;
    }
    void encodeInt16(CAN_Message &message, uint8_t startByte, int16_t value)
    {
        if (startByte + sizeof(int16_t) >= message.length)
        {

            return;
        }

        message.payload[startByte] = (value >> 8) & 0xFF;
        message.payload[startByte + 1] = (value) & 0xFF;
    }
    int16_t decodeInt16(const CAN_Message &message, uint16_t startByte)
    {
        if (startByte + sizeof(int16_t) >= message.length)
        {
            return -1;
        }
        return (static_cast<int16_t>(message.payload[startByte]) << 8) |
               (static_cast<int16_t>(message.payload[startByte + 1]));
    }
}