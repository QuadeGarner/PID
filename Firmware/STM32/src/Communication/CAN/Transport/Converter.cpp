#include "Converter.h"
#include "Arduino.h"
CAN_Frame Converter::convertToFrame(const CAN_Message &message)
{
    Serial.print("Entering convertToFrame");
    CAN_Frame frame{};
    frame.id = message.identifier.getRawIdentifier();
    frame.dlc = message.length;
    for (int i = 0; i < 8; i++)
    {
        frame.data[i] = message.payload[i];
    }
    Serial.print("Leaving convertToFrame");
    return frame;
}
CAN_Message Converter::convertToMessage(const CAN_Frame &frame)
{
    Serial.print("Entering convertToMessage");
    CAN_Message returnMessage;
    returnMessage.identifier = J1939Identifier(frame.id);
    returnMessage.length = frame.dlc;
    for (int i = 0; i < frame.dlc; i++)
    {
        returnMessage.payload[i] = frame.data[i];
    }
    Serial.print("Leaving convertToMessage");
    return returnMessage;
}