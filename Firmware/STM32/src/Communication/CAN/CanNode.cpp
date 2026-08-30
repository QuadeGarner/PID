#include "CanNode.h"
void CanNode::send(const CAN_Frame &cf)
{
    cm.broadcast(cf);
}
void CanNode::receive(const CAN_Frame &cf)
{
    ifc.receiveFrame(cf);
}
CanNode::CanNode(DeviceID id, CanBusManager &manager, IFrameReceiver &receiver) : id(id), cm(manager), ifc(receiver)
{
    manager.connect(*this);
}