#include "SERIALMANAGER.h"

void SerialManager::getData(){
    if(determineTimeOut()){
        currentState = CurrentState::TIMEOUT;
    }
    while(Serial.avaiable() && currentState !=CurrentState::TIMEOUT){
        readCharacter = readByte();
        lastRead = millis();
    }
}
char SerialManager::getReadCharacter(){
    return readCharacter;
}
char SerialManager::readByte(){
    return Serial.read();
}

bool SerialManager:: determineTimeOut(){
    // one spot only to change if timeout need to be longer or shorter
    if(millis() - lastRead > 5000){
        return true;
    }
    retrun false;
}