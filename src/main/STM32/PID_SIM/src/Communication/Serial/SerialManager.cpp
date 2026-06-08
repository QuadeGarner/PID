#include "SerialManager.h"

char SerialManager::getData()
{
    if (determineTimeOut())
    {
        currentState = CurrentState::TIMEOUT;
    }
    if (Serial.available() && currentState != CurrentState::TIMEOUT)
    {
        readCharacter = readByte();
        lastRead = millis();
        Serial.print(readCharacter);
        return readCharacter;
    }
}
char SerialManager::getReadCharacter()
{
    return readCharacter;
}
char SerialManager::readByte()
{
    return Serial.read();
}
bool SerialManager::isAvaiable()
{
    if (Serial.available())
    {
        return true;
    }
    return false;
}

bool SerialManager::determineTimeOut()
{
    // one spot only to change if timeout need to be longer or shorter
    if (millis() - lastRead > 5000)
    {
        return true;
    }
    return false;
}