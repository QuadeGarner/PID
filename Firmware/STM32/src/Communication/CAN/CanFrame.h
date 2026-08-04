#ifndef FRAME
#define FRAME
#include <cstdint>
struct CAN_Frame
{
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
};
#endif
// 0x100 = MotorCommand
// 0x101 = PID_UPDATE
// 0x102 = ENCODER_STATUS
// 0x200 = Telemetry
// 0x300 = Diagnostics