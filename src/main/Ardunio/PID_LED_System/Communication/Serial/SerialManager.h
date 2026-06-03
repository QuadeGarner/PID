#ifndef SERIALMANAGER
#define SERIALMANAGER
#include "CURRENTSTATE.h"
class SerialManager{
    private:
        CurrentState currentState = WAITING_FOR_DATA;
        char readCharacter;
        long lastRead =0;
        char readByte();
    public:
        char getData();
        char getReadCharacter();
        bool determineTimeOut();
};
#endif