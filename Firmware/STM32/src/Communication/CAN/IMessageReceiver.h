#pragma once
#include "./Transport/Transport.h"
class IMessageReceiver
{
public:
    virtual void receiveMessage(const CAN_Message &) = 0;
    virtual ~IMessageReceiver() = default;
};