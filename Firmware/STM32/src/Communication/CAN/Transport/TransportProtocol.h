#ifndef TRANSPORTPROTOCOL
#define TRANSPORTPROTOCOL
#include "Transport.h"
#include "TransportState.h"
#include "../../CAN/CanFrame.h"
struct FrameBuffer
{
    CAN_Frame frames[64];
    uint16_t count;
};
class TransportProtocol
{
private:
    TransportState transportState = TransportState::IDLE;
    uint16_t numberOfFrames;
    uint32_t messageId;
    uint16_t messageLength;
    uint16_t framesReceived;
    bool received[255];
    uint8_t buffer[1785];
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
};

#endif