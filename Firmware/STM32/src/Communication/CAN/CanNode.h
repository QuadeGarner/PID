#ifndef CANNODE
#define CANNODE
#include <stdint.h>
#include "CanBusManager.h"
#include "MotorCommand.h"
#include "../src/Communication/CAN/IFrameReceiver.h"

class CanNode
{
private:
    DeviceID id;
    CanBusManager &cm;
    IFrameReceiver &ifc;

public:
    CanNode(DeviceID, CanBusManager &, IFrameReceiver &);
    void send(const CAN_Frame &);
    void receive(const CAN_Frame &);
};
#endif