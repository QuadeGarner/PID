#include "TestNode.h"
void TestNode::receive(CAN_Frame &frame)
{
    std::cout << name
              << " received frame with ID 0x"
              << std::hex << frame.id
              << std::dec
              << std::endl;
}
CanNode &TestNode::getNode()
{
    return node;
}
TestNode::TestNode(const char *nodeName, DeviceID id, CanBusManager &manager) : name(nodeName), node(id, manager, *this) {}