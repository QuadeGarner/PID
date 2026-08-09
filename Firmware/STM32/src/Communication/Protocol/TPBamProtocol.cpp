#include "./TPBamProtocol.h"
#include "../src/Librays/CanCodec.h"
CAN_Message TPBamProtocol::create(const CAN_Message &originalMessage)
{
    int16_t frameCount = (originalMessage.length + 6) / 7;
    CAN_Message message{};
    message.messageID = TP_BAM;
    message.length = 8;
    CanCodec::encodeInt16(message, 0, originalMessage.length);
    CanCodec::encodeInt16(message, 2, frameCount);
    CanCodec::encodeInt32(message, 4, originalMessage.messageID);
    return message;
}
int32_t TPBamProtocol::getOriginalMessageId(const CAN_Message &message)
{
    return CanCodec::decodeInt32(message, 4);
}
int16_t TPBamProtocol::getFrameCount(const CAN_Message &message)
{
    return CanCodec::decodeInt16(message, 2);
}
int16_t TPBamProtocol::getOriginalMessageLength(const CAN_Message &message)
{
    return CanCodec::decodeInt16(message, 0);
}
