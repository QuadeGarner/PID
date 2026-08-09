#include "MotorController.h"

MotorController::MotorController(VirtualMotor &vm, CanBusManager &bus) : vm(vm), cm(DeviceID::MOTOR_CONTROLLER, bus, *this) {}
void MotorController::receiveMessage(const CAN_Message &message)
{
    switch (message.messageID)
    {
    case MOTOR_COMMAND:
    {

        float power = MotorCommandProtocol::getPower(message);
        vm.update(power, getCycleTime());

        cm.send(MotorStatusProtocol::create(vm.getPosition(), vm.getVelocity()));
        break;
    }
    case CONTROL_SYNC:
    {

        uint32_t tick = ControlSyncProtocol::getTickCount(message);
        if (tick > tickCount)
        {
            tickCount = tick;
            currentTime = ControlSyncProtocol::getTime(message);
        }
        break;
    }
    default:
    {
        // Ignore all other Can Messages
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
