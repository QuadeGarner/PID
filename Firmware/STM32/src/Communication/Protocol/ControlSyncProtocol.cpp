#include "ControlSyncProtocol.h"
CAN_Message ControlSyncProtocol::create(float time, uint32_t tickCount)
{
    CAN_Message controlSync{};
    J1939Identifier controlIdentifier = J1939Identifier(6, false, false, 0xFF, 0x01, DeviceID::MOTION_COORDINATOR);
    controlSync.identifier = controlIdentifier;
    controlSync.length = 8;
    CanCodec::encodeFloat(controlSync, 0, time);
    CanCodec::encodeInt32(controlSync, 4, tickCount);
    return controlSync;
}
float ControlSyncProtocol::getTime(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 0);
}
uint32_t ControlSyncProtocol::getTickCount(const CAN_Message &message)
{
    return CanCodec::decodeInt32(message, 4);
}