#pragma once
#define MOTORCONTROLLER
#include "../Communication/CAN/CanNode.h"
#include "./VitrualMotor/VirtualMotor.h"
#include "../Communication/CAN/ICanReceiver.h"
class MotorController : public ICanReceiver
{
private:
    CanNode cn;
    VirtualMotor vm;
    float currentTime;
    float lastTime;
    uint32_t tickCount;
    float getCycleTime();

public:
    MotorController(VirtualMotor &, CanBusManager &);
    void receive(CAN_Frame &) override;
    Can_Frame buildMotorStatus();
}