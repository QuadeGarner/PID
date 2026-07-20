#include "CanCodec.h"

namespace CanCodec
{
    // Store a signed 32-bit int into four bytes
    void encodeInt32(Can_Frame &frame, uint8_t startByte, int32_t value)
    {
        if (startByte > 4)
        {
            std::cerr << " Invlaid startByte" << std::endl;
            return;
        }

        frame.data[startByte] = (value >> 24) & 0xFF;
        frame.data[startByte + 1] = (value >> 16) & 0xFF;
        frame.data[startByte + 2] = (value >> 8) & 0xFF;
        frame.data[startByte + 3] = value & 0xFF;
    }
    // Decodes a 32 bit int from 4 bytes
    int32_t decodeInt32(const Can_Frame &frame, uint8_t startByte)
    {
        if (startByte > 4)
        {
            std::cerr << "Invalid startByte " << std::endl;
            return -1;
        }
        return (static_cast<int32_t>(frame.data[startByte]) << 24) |
               (static_cast<int32_t>(frame.data[startByte + 1]) << 16) |
               (static_cast<int32_t>(frame.data[startByte + 2]) << 8) |
               (static_cast<int32_t>(frame.data[startByte + 3]));
    }
    // Encodes a float by scaling and storing it as an int32
    void encodeFloat(Can_Frame &frame, uint8_t startByte, float value, float scale)
    {
        int32_t intValue = static_cast<int32_t>(value * scale);
        encodeInt32(frame, startByte, intValue);
    }
    // decodes a scaled int32 back into a float
    float decodeFloat(const CAN_Frame &frame, uint8_t startByte, float scale)
    {
        int32_t value = decodeInt32(frame, startByte);
        return static_cast<float>(value) / scale;
    }
}