#include "./TPBamProtocol.h"
#include "../src/Librays/CanCodec.h"
CAN_Message TPBamProtocol::create(const CAN_Message &originalMessage)
{
    J1939Identifier originalIdentifier = J1939Identifier(originalMessage.messageID);
    J1939Identifier BAMIdentifier = J1939Identifier(7, false, 0xec, 0xff, originalIdentifier.getSourceAddress());
    CAN_Message message{};
    message.messageID = BAMIdentifier.getRawIdentifier();
    uint32_t pgn = originalIdentifier.getPGN();

    uint16_t packectCount = (originalMessage.length + 6) / 7;
    message.length = 8;
    message.payload[0] = 0x20;
    message.payload[1] = originalMessage.length & 0xff;
    message.payload[2] = (originalMessage.length >> 8) & 0xff;
    message.payload[3] = packectCount;
    message.payload[4] = 0xff;
    message.payload[5] = pgn & 0xff;
    message.payload[6] = (pgn >> 8) & 0xff;
    message.payload[7] = (pgn >> 16) & 0xff;
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
