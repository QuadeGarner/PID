#include "CanNode.h"
void CanNode::send(CAN_Frame &cf)
{
    cm.broadcast(cf);
}
void CanNode::receive(CAN_Frame &cf)
{
    ic.receive(cf);
}
CanNode::CanNode(DeviceID id, CanBusManager &manager, ICanReceiver &receiver) : id(id), cm(manager), ic(receiver) {}