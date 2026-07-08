#ifndef FRAME
#define FRAME
#include <cstdint>
struct CAN_Frame
{
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
};
// 0x10 = Target
// 0x11 = kP
// 0x12 = ki
// 0x13 = kd

#endif