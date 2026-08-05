#include "MotorStatusProtocol.h"
#include "../src/Librays/CanCodec.h"
#include "../CAN/Transport/Transport.h"
#include "../CAN/CanProtocol.h"
CAN_Message MotorStatusProtocol::create(float position, float velocity)
{
    CAN_Message motorStatus{};
    motorStatus.messageID = MOTOR_STATUS;
    motorStatus.length = 8;
    CanCodec::encodeFloat(motorStatus, 0, position);
    CanCodec::encodeFloat(motorStatus, 4, velocity);
    return motorStatus;
}
float MotorStatusProtocol::getPosition(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 0);
}
float MotorStatusProtocol::getVelocity(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 4);
}
