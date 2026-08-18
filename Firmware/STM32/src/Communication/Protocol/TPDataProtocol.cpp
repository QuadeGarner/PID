#include "TPDataProtocol.h"
CAN_Message TPDataProtocol::create(const CAN_Message &originalMessage, uint8_t sequence)
{
    J1939Identifier originalIdentifier = J1939Identifier(originalMessage.messageID);
    J1939Identifier dataIdentifier = J1939Identifier(7, false, 0xeb, 0xff, originalIdentifier.getSourceAddress());
    CAN_Message message{};
    message.messageID = dataIdentifier.getRawIdentifier();
    message.length = 8;
    uint16_t start = (sequence - 1) * 7;
    for (int i = 0; i < 7; i++)
    {
        if (start + i < originalMessage.length)
        {
            message.payload[i + 1] = originalMessage.payload[start + i];
        }
        else
        {
            message.payload[i + 1] = 0xff;
        }
    }
    message.payload[0] = sequence;
    return message;
}