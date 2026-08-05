#include "TransportProtocol.h"
#include "../../Protocol/TPBamProtocol.h"

bool TransportProtocol::messageReady() const
{
    return transportState == TransportState::COMPLETE;
}
CAN_Message TransportProtocol::getMessage()
{
    return completedMessage;
}
std::vector<CAN_Frame> TransportProtocol::buildFrames(const CAN_Message &message)
{
    if (message.length <= 8)
    {
        return {buildSingleFrame(message)};
    }
    else
    {
        return fragmentMessage(message);
    }
}
// create a CAN_Frame
CAN_Frame TransportProtocol::buildSingleFrame(const CAN_Message &message)
{
    CAN_Frame frame{};
    frame.id = message.messageID;
    frame.dlc = message.length;
    for (uint8_t i = 0; i < message.length; i++)
    {
        frame.data[i] = message.payload[i];
    }
    return frame;
}
std::vector<CAN_Frame> TransportProtocol::fragmentMessage(const CAN_Message &message)
{
    CAN_Message bam = TPBamProtocol::create(message);
    uint16_t numberOfFrames = TPBamProtocol::getFrameCount(bam);
    std::vector<CAN_Frame> frames;
    frames.push_back(buildSingleFrame(bam));
    for (uint16_t i = 0; i < numberOfFrames; i++)
    {
        CAN_Frame frame{};
        frame.id = TP_DATA;
        if ((i + 1) * 7 < message.length)
        {
            frame.dlc = 8;
        }
        else
        {
            frame.dlc = message.length % 7 + 1;
        }
        frame.data[0] = (uint8_t)i + 1;
        for (uint8_t j = (i * 7); j < (i * 7) + 7; j++)
        {

            if (j >= message.length)
            {
                break;
            }
            frame.data[(j % 7) + 1] = message.payload[j];
        }

        frames.push_back(frame);
    }
    return frames;
}
bool TransportProtocol::receiveFrame(const CAN_Frame &frame)
{
    switch (frame.id)
    {
    case TP_BAM:
    {
        reset();
        CAN_Message bam = buildSingleMessage(frame);
        messageId = TPBamProtocol::getOriginalMessageId(bam);
        messageLength = TPBamProtocol::getOriginalMessageLength(bam);
        numberOfFrames = TPBamProtocol::getFrameCount(bam);
        break;
    }
    case TP_DATA:
    {
        storeFragments(frame);
        if (transportState == TransportState::RECEIVING_COMPLETE)
        {
            completedMessage = buildMessageFromFragment();
            transportState = TransportState::COMPLETE;
            transferActive = false;
        }
        break;
    }
    default:
        break;
    }
    return messageReady();
}
CAN_Message TransportProtocol::buildSingleMessage(const CAN_Frame &frame)
{
    CAN_Message message{};
    message.messageID = frame.id;
    message.length = frame.dlc;
    for (uint8_t i = 0; i < frame.dlc; i++)
    {
        message.payload[i] = frame.data[i];
    }
    return message;
}
CAN_Message TransportProtocol::buildMessageFromFragment()
{
    CAN_Message message{};
    message.messageID = messageId;
    message.length = messageLength;
    for (int i = 0; i < messageLength; i++)
    {
        message.payload[i] = buffer[i];
    }
    return message;
}
void TransportProtocol::storeFragments(const CAN_Frame &frame)
{
    uint8_t sequence = frame.data[0];
    uint8_t payloadBytes = frame.dlc - 1;
    if (!received[sequence])
    {
        uint16_t start = (sequence - 1) * 7;
        for (int j = 0; j < payloadBytes; j++)
        {
            buffer[start + j] = frame.data[j + 1];
        }
        framesReceived++;
        received[sequence] = true;
    }
    if (framesReceived == numberOfFrames)
    {
        transportState = TransportState::RECEIVING_COMPLETE;
    }
}
void TransportProtocol::reset()
{
    framesReceived = 0;
    transferActive = true;
    transportState = TransportState::RECIEVING;
    for (int i = 0; i < std::size(received); i++)
    {
        received[i] = false;
    }
}