#ifndef CANBUSMANAGER
#define CANBUSMANAGER
#include "CanFrame.h"
class CanNode;
class CanBusManager
{
private:
    CanNode *bus[32];

public:
    void connect(CanNode &);
    void broadcast(const CAN_Frame &);
};
#endif