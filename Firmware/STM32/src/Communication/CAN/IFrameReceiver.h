#pragma once
#include "CanFrame.h"
class IFrameReceiver
{
public:
    virtual void receiveFrame(const CAN_Frame &) = 0;
    virtual ~IFrameReceiver() = default;
};
