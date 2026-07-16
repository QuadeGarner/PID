#ifndef ICAN
#define ICAN
#include "CanFrame.h"
class ICanReceiver
{
public:
    virtual void receive(CAN_Frame &) = 0;
    virtual ~ICanReceiver() = default;
};
#endif