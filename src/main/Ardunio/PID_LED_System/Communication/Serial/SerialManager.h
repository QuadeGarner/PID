#ifndef SERIALMANAGER
#define SERIALMANAGER
#include "../../Enums/CurrentStates.h"
class SerialManager
{
private:
    CurrentState currentState = CurrentState::WAITING_FOR_DATA;
    char readCharacter;
    long lastRead = 0;
    char readByte();

public:
    char getData();
    char getReadCharacter();
    bool determineTimeOut();
    bool isAvaiable();
};
#endif