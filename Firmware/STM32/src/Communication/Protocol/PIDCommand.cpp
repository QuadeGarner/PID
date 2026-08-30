#include "PIDCommand.h"
CAN_Message PIDCommandProtocol::create(float target, float position)
{
    CAN_Message pidCommand{};
    pidCommand.identifier = PID_COMMAND;
    pidCommand.length = 8;
    CanCodec::encodeFloat(pidCommand, 0, target);
    CanCodec::encodeFloat(pidCommand, 4, position);
    return pidCommand;
}
float PIDCommandProtocol::getTarget(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 0);
}
float PIDCommandProtocol::getPosition(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 4);
}