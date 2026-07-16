#include "MotorController.h"
MotorController::MotorController(VirtualMotor &vm, CanBusManager &bus) : vm(vm), cn(DeviceID::MOTOR_CONTORLLER, bus, *this) {}
void MotorController::receive(CAN_Frame &frame)
{
    switch (frame.id)
    {
    case MOTOR_COMMAND:
        // do something
        break;

    default:
        // do nothing
        break;
    }
}