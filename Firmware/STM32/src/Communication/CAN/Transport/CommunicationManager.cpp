#include "CommunicationManager.h"
void CommunicationManager::send(const CAN_Message &message)
{
    if (message.length <= 8)
    {

        node.send(Converter::convertToFrame(message));
    }
    else
    {
        tp.startTransfer(message);
    }
}

void CommunicationManager::receiveFrame(const CAN_Frame &frame)
{
    CAN_Message message = Converter::convertToMessage(frame);

    uint32_t pgn = message.identifier.getPGN();

    if (pgn == TP_CM_PGN || pgn == TP_DT_PGN)
    {
        tp.receiveMessage(message);

        if (tp.messageReady())
        {
            application.receiveMessage(tp.getMessage());
        }
    }
    else
    {
        application.receiveMessage(message);
    }
}
CommunicationManager::CommunicationManager(DeviceID id, CanBusManager &bus, IMessageReceiver &receiver) : node(id, bus, *this), application(receiver) {}

void CommunicationManager::process()
{
    CAN_Message message = tp.process();
    if (message.length == 0)
    {
        return;
    }
    node.send(Converter::convertToFrame(message));
}