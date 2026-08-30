#ifndef TRANSPORTPROTOCOL
#define TRANSPORTPROTOCOL
#include "Transport.h"
#include "Communication/CAN/SAEJ1939/Enums/TransferProtocolEnums.h"
class TransportProtocol
{
private:
    // Receiving
    TransferStates receivingState = TransferStates::IDLE;
    uint16_t receivingNumberOfFrames;
    uint16_t framesReceived;
    bool receivedSequence[255];
    uint8_t buffer[1785];
    uint32_t messageId;
    uint16_t messageLength;
    CAN_Message completedMessage;
    uint32_t originalPGN = 0;
    DeviceID sourceAddress = DeviceID::NONE;
    uint8_t priority = 0;
    // Sending
    TransferStates sendingState = TransferStates::IDLE;
    uint16_t sendingNumberOfFrames;
    uint16_t currentSequence;
    CAN_Message currentMessage;
    // helper functions
    void reset();
    void storeFragments(const CAN_Message &);
    CAN_Message buildMessageFromFragments();

public:
    bool receiveMessage(const CAN_Message &);
    bool messageReady() const;
    CAN_Message getMessage();
    void startTransfer(const CAN_Message &);
    CAN_Message process();
    J1939Identifier getIdentifier() const;
};

#endif