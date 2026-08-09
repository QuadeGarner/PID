#pragma once
#define MOTORCONTROLLER
#include "../Communication/CAN/CanNode.h"
#include "./VitrualMotor/VirtualMotor.h"
#include "../Communication/CAN/IMessageReceiver.h"
#include "../src/Communication/CAN/CanProtocol.h"
#include "../src/Communication/CAN/Transport/CommunicationManager.h"
#include "../../src/Librays/CanCodec.h"
#include "Communication/Protocol/MotorStatusProtocol.h"
#include "Communication/Protocol/MotorCommandProtocol.h"
#include "Communication/Protocol/ControlSyncProtocol.h"
class MotorController : public IMessageReceiver
{
private:
    CommunicationManager cm;
    VirtualMotor vm;
    float currentTime;
    float lastTime;
    uint32_t tickCount;
    float getCycleTime();

public:
    MotorController(VirtualMotor &, CanBusManager &);
    void receiveMessage(const CAN_Message &) override;
};