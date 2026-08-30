#pragma once
#include "../CanNode.h"
#include "../src/Communication/CAN/IFrameReceiver.h"
#include "TransportProtocol.h"
#include "../src/Communication/CAN/IMessageReceiver.h"
#include "Converter.h"
class CommunicationManager : public IFrameReceiver
{
private:
    CanNode node;
    TransportProtocol tp;
    IMessageReceiver &application;

public:
    void send(const CAN_Message &);
    void receiveFrame(const CAN_Frame &) override;
    CommunicationManager(DeviceID, CanBusManager &, IMessageReceiver &);
    void process();
};