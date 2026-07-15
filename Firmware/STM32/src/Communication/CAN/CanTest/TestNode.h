#ifndef TESTNODE
#define TESTNODE
#include "ICanReceiver.h"
#include "CanNode.h"
#include <iostream>
class TestNode : public ICanReceiver
{
private:
    const char *name;
    CanNode node;

public:
    TestNode(const char *name, DeviceID id, CanBusManager &manager);
    void receive(CAN_Frame &) override;
    CanNode &getNode();
};
#endif