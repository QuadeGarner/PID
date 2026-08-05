#include "MotorController.h"

MotorController::MotorController(VirtualMotor &vm, CanBusManager &bus) : vm(vm), cm(DeviceID::MOTOR_CONTROLLER, bus, *this) {}
void MotorController::receiveMessage(const CAN_Message &message)
{
    switch (message.messageID)
    {
    case MOTOR_COMMAND:
    {

        float power = CanCodec::decodeFloat(message, 0);
        vm.update(power, getCycleTime());

        cm.send(buildMotorStatus());
        break;
    }
    case CONTROL_SYNC:
    {
        // currentTime = CanCodec::decodeFloat(frame, 0);
        uint32_t tick = CanCodec::decodeInt32(message, 4);
        if (tick > tickCount)
        {
            tickCount = tick;
            currentTime = CanCodec::decodeFloat(message, 0);
        }
        break;
    }
    default:
    {
        // Ignore all other Can Frames
        break;
    }
    }
}
float MotorController::getCycleTime()
{
    float cycleTime = currentTime - lastTime;
    lastTime = currentTime;
    return cycleTime;
}
CAN_Message MotorController::buildMotorStatus()
{
    CAN_Message status{};
    status.messageID = MOTOR_STATUS;
    status.length = 8;
    CanCodec::encodeFloat(status, 0, vm.getPosition());
    CanCodec::encodeFloat(status, 4, vm.getVelocity());
    return status;
}
