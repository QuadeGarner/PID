#include "CanBusManager.h"
#include "CanNode.h"
void CanBusManager::connect(CanNode &node)
{
    for (int i = 0; i < 31; i++)
    {
        if (bus[i] == nullptr)
        {
            bus[i] = &node;
            break;
        }
    }
}
void CanBusManager::broadcast(CAN_Frame &frame)
{
    for (CanNode *n : bus)
    {
        if (n != nullptr)
        {
            n->receive(frame);
        }
        else
        {
            break;
        }
    }
}