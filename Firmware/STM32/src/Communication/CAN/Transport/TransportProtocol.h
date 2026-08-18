#ifndef TRANSPORTPROTOCOL
#define TRANSPORTPROTOCOL
#include "Transport.h"
#include "Communication/CAN/SAEJ1939/Enums/TransferProtocolEnums.h"
#include "../../CAN/CanFrame.h"
struct FrameBuffer
{
    CAN_Frame frames[64];
    uint16_t count;
};
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
    // Sending
    TransferStates sendingState = TransferStates::IDLE;
    uint16_t sendingNumberOfFrames;
    uint16_t currentSequence;
    CAN_Message currentMessage;
    // frame creation

    CAN_Frame buildSingleFrame(const CAN_Message &);
    FrameBuffer fragmentMessage(const CAN_Message &);
    CAN_Message buildSingleMessage(const CAN_Frame &);
    CAN_Message buildMessageFromFragment();
    void storeFragments(const CAN_Frame &);
    CAN_Message completedMessage;
    void reset();

public:
    bool receiveFrame(const CAN_Frame &);
    bool messageReady() const;
    CAN_Message getMessage();
    FrameBuffer buildFrames(const CAN_Message &);
    void startTransfer(const CAN_Message &);
};

#endif