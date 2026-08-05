#include "./PIDStatusProtocol.h"
#include "../src/Communication/CAN/Transport/Transport.h"
#include "../CAN/CanProtocol.h"
#include "../src/Librays/CanCodec.h"

CAN_Message PidStatusProtocol::create(float power, float error, float lastError)
{
    CAN_Message pidStatus{};
    pidStatus.messageID = PID_STATUS;
    pidStatus.length = 12;
    CanCodec::encodeFloat(pidStatus, 0, power);
    CanCodec::encodeFloat(pidStatus, 4, error);
    CanCodec::encodeFloat(pidStatus, 8, lastError);
    return pidStatus;
}
float PidStatusProtocol::getError(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 4);
}
float PidStatusProtocol::getOutput(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 0);
}
float PidStatusProtocol::getLastError(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 8);
}