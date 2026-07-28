#ifndef TRANSPORTPROTOCOL
#define TRANSPORTPROTOCOL
#include "Transport.h"
class TransportProtocol
{
private:
    uint16_t numberOfFrames;
    bool transferActive = false;
    uint32_t messageId;
    uint16_t messageLength;
    uint16_t framesReceived;
    uint8_t buffer[1785];

public:
    bool receiveFrame(const CAN_Frame &);
    bool messageReady() const;
    CAN_Message getMessage();
    void sendMessage(const CAN_Message &);
}