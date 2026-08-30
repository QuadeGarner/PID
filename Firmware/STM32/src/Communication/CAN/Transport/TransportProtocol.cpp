#include "TransportProtocol.h"
#include "../../Protocol/TPBamProtocol.h"
#include "../../Protocol/TPDataProtocol.h"

bool TransportProtocol::messageReady() const
{
    return receivingState == TransferStates::COMPLETE;
}
CAN_Message TransportProtocol::getMessage()
{
    receivingState = TransferStates::IDLE;
    return completedMessage;
}
bool TransportProtocol::receiveMessage(const CAN_Message &message)
{
    J1939Identifier identifier = J1939Identifier(message.identifier);

    switch (identifier.getPGN())
    {
        // needs to change to the PGN of TC / BAM
    case TP_CM_PGN:
    {
        reset();
        receivingNumberOfFrames = TPBamProtocol::getPacketCount(message);
        receivingState = TransferStates::DATA;
        messageLength = TPBamProtocol::getMessageLength(message);
        originalPGN = TPBamProtocol::getPGN(message);
        sourceAddress = static_cast<DeviceID>(identifier.getSourceAddress());
        priority = identifier.getPriority();
        break;
    }
    // need to change to the PGN
    case TP_DT_PGN:
    {
        storeFragments(message);
        if (receivingState == TransferStates::COMPLETE)
        {
            completedMessage = buildMessageFromFragments();
        }
        break;
    }
    default:
        break;
    }
    return messageReady();
}
void TransportProtocol::reset()
{
    framesReceived = 0;
    for (int i = 0; i < sizeof(buffer); i++)
    {
        buffer[i] = 0;
    }
    for (int i = 0; i < sizeof(receivedSequence); i++)
    {
        receivedSequence[i] = false;
    }
    receivingState = TransferStates::IDLE;
    originalPGN = 0;
    completedMessage = CAN_Message{};
    messageLength = 0;
}
void TransportProtocol::startTransfer(const CAN_Message &message)
{
    if (sendingState != TransferStates::IDLE)
    {
        return;
    }
    currentMessage = message;
    sendingNumberOfFrames = (message.length + 6) / 7;
    currentSequence = 1;
    sendingState = TransferStates::BAM;
}
CAN_Message TransportProtocol::process()
{
    switch (sendingState)
    {
    case TransferStates::IDLE:
        return CAN_Message{};
    case TransferStates::BAM:
        sendingState = TransferStates::DATA;
        return TPBamProtocol::create(currentMessage);
    case TransferStates::DATA:
    {

        CAN_Message dataMessage = TPDataProtocol::create(currentMessage, currentSequence);
        currentSequence++;
        if (currentSequence == sendingNumberOfFrames + 1)
        {
            sendingState = TransferStates::IDLE;
        }
        return dataMessage;
    }
    default:
        return CAN_Message{};
    }
}
void TransportProtocol::storeFragments(const CAN_Message &message)
{
    uint8_t sequence = message.payload[0];

    if (!receivedSequence[sequence] && sequence != 0 && sequence <= receivingNumberOfFrames)
    {
        uint16_t start = (sequence - 1) * 7;
        uint16_t remaining = messageLength - start;
        for (int j = 0; j < 7 && j < remaining; j++)
        {
            buffer[start + j] = message.payload[j + 1];
        }
        framesReceived++;
        receivedSequence[sequence] = true;
    }
    if (framesReceived == receivingNumberOfFrames)
    {
        receivingState = TransferStates::COMPLETE;
    }
}
CAN_Message TransportProtocol::buildMessageFromFragments()
{
    CAN_Message message{};
    message.identifier = getIdentifier();
    message.length = messageLength;
    for (int i = 0; i < messageLength; i++)
    {
        message.payload[i] = buffer[i];
    }
    return message;
}
J1939Identifier TransportProtocol::getIdentifier() const
{
    uint8_t ps = (originalPGN & 0xFF);
    uint8_t pf = (originalPGN >> 8) & 0xFF;
    bool dataPage = (originalPGN >> 16) & 0x01;
    if (pf < 240)
    {
        return J1939Identifier(priority, false, dataPage, pf, 0, sourceAddress);
    }
    else
    {
        return J1939Identifier(priority, false, dataPage, pf, ps, sourceAddress);
    }
}
