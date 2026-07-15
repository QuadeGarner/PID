#ifndef CANNODE
#define CANNODE
#include <stdint.h>
#include "CanBusManager.h"
#include "MotorCommand.h"
#include "ICanReceiver.h"

class CanNode
{
private:
    DeviceID id;
    CanBusManager &cm;
    ICanReceiver &ic;

public:
    CanNode(DeviceID, CanBusManager &, ICanReceiver &);
    void send(CAN_Frame &);
    void receive(CAN_Frame &);
};
#endif