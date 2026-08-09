#include "CommunicationManager.h"
void CommunicationManager::send(const CAN_Message &message)
{
    FrameBuffer frames = tp.buildFrames(message);
    for (uint16_t i = 0; i < frames.count; i++)
    {
        node.send(frames.frames[i]);
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
