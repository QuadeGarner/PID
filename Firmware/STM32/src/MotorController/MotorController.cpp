#include "MotorController.h"
#include "../Librays/CanCodec.h"
MotorController::MotorController(VirtualMotor &vm, CanBusManager &bus) : vm(vm), cn(DeviceID::MOTOR_CONTROLLER, bus, *this) {}
void MotorController::receive(CAN_Frame &frame)
{
    switch (frame.id)
    {
    case MOTOR_COMMAND:
    {
        // do something
        float power = CanCodec::decodeFloat(frame, 0);
        vm.update(power, getCycleTime());

        cn.send(buildMotorStatus());
        break;
    }
    case CONTROL_SYNC:
    {
        // currentTime = CanCodec::decodeFloat(frame, 0);
        tick = CanCodec::decodeInt32(frame, 4);
        if (tick > tickCount)
        {
            tickCount = tick;
            currentTime = CanCodec::decodeFloat(frame, 0);
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
Can_Frame MotorController::buildMotorStatus()
{
    Can_Frame status{};
    status.id = MOTOR_STATUS;
    status.dlc = 8;
    CanCodec::encodeFloat(status, 0, vm.getPosition());
    CanCodec::encodeFloat(status, 4, vm.getVelocity());
    return status;
}