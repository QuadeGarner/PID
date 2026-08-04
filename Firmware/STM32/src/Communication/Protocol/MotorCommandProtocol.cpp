#include "MotorCommandProtocol.h"
#include "../CAN/Transport/Transport.h"
#include "../CAN/CanProtocol.h"
#include "../Librays/CanCodec.h"

static CAN_Message MotorCommandProtocol::create(float power)
{
    CAN_Message motorCommand{};
    motorCommand.messageID = MOTOR_COMMAND;
    motorCommand.length = 4;
    CanCodec::encodeFloat(motorCommand, 0, power);
    return motorCommand;
}
static float MotorCommandProtocol::getPower(const CAN_Message &message)
{
    return CanCodec::decodeFloat(message, 0);
}