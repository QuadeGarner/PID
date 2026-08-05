#include "CommunicationManager.h"
void CommunicationManager::send(const CAN_Message &message)
{
    std::vector<CAN_Frame> frames = tp.buildFrames(message);
    for (const CAN_Frame &frame : frames)
    {
        node.send(frame);
    }
}
void CommunicationManager::receiveFrame(const CAN_Frame &frame)
{
    tp.receiveFrame(frame);
    if (tp.messageReady())
    {
        application.receiveMessage(tp.getMessage());
    }
}
CommunicationManager::CommunicationManager(DeviceID id, CanBusManager &bus, IMessageReceiver &receiver) : node(id, bus, *this), application(receiver) {}
