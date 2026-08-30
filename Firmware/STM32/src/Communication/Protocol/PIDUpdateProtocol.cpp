#include "PIDUpdateProtocol.h"
CAN_Message PIDUpdateProtocol::create(float kP, float kI, float kD)
{
    CAN_Message pidUpdate{};
    pidUpdate.identifier = PID_UPDATE;
    pidUpdate.length = 12;
    CanCodec::encodeFloat(pidUpdate, 0, kP);
    CanCodec::encodeFloat(pidUpdate, 4, kI);
    CanCodec::encodeFloat(pidUpdate, 8, kD);
    return pidUpdate;
}
float PIDUpdateProtocol::getKP(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 0);
}
float PIDUpdateProtocol::getKI(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 4);
}
float PIDUpdateProtocol::getKD(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 8);
}