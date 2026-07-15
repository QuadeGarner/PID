
#ifndef CAN_PROTOCOL
#define CAN_PROTOCOL
#include <cstdint>
constexpr uint32_t MOTOR_COMMAND = 0x100;
constexpr uint32_t PID_UPDATE = 0x101;
constexpr uint32_t MOTOR_STATUS = 0x200;
constexpr uint32_t ENCODER_STATUS = 0x201;
constexpr uint32_t HEARTBEAT = 0x300;
constexpr uint32_t FAULTREPORT = 0x400;
constexpr int MAX_CAN_DATA_LENGTH = 8;
#endif
/**
 * Ranges for Future Commands
 * 0x100 - 0x1FF   Motion Control
 * 0x200 - 0x2FF   Telemetry
 * 0x300 - 0x3FF   Diagnostics
 * 0x400 - 0x4FF   Sensors
 * 0x500 - 0x5FF   System
 */