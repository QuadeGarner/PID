#include "./TPBamProtocol.h"
#include "../src/Librays/CanCodec.h"
CAN_Message TPBamProtocol::create(const CAN_Message &originalMessage)
{
    J1939Identifier originalIdentifier = J1939Identifier(originalMessage.identifier);
    J1939Identifier BAMIdentifier = J1939Identifier(7, false, false, 0xec, 0xff, static_cast<DeviceID>(originalIdentifier.getSourceAddress()));
    CAN_Message message{};
    message.identifier = BAMIdentifier.getRawIdentifier();
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
uint16_t TPBamProtocol::getMessageLength(const CAN_Message &message)
{
    uint16_t messageLength = (message.payload[2] << 8) | (message.payload[1]);
    return messageLength;
}
uint16_t TPBamProtocol::getPacketCount(const CAN_Message &message)
{
    return message.payload[3];
}
uint32_t TPBamProtocol::getPGN(const CAN_Message &message)
{
    uint32_t pgn = (message.payload[7] << 16) | (message.payload[6] << 8) | message.payload[5];
    return pgn;
}
