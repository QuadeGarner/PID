#ifndef SERIALMANAGER
#define SERIALMANAGER
#include "PacketParser.h"
#include "CURRENTSTATE.h"
class SerialManager{
    private:
        CurrentState currentState = WAITING_FOR_DATA;
        char readCharacter;
        long lastRead =0;
        char readByte();
        PacketParser pp;
    public:
        char getData();
        char getReadCharacter();
        bool determineTimeOut();
        bool isAvaiable();
};
#endif