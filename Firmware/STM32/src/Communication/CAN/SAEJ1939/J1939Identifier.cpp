#include "J1939Identifier.h"
J1939Identifier::J1939Identifier(uint8_t p, bool dp, uint8_t pf, uint8_t ps, uint8_t sa)
{
    rawIdentifier = ((p & 0x07) << 26) | ((dp & 0x01) << 24) | ((pf) << 16) | (ps << 8) | sa;
}
J1939Identifier::J1939Identifier(uint32_t messageID)
{
    rawIdentifier = (messageID & 0x1FFFFFFF);
}
uint8_t J1939Identifier::getPriority()
{
    return (rawIdentifier >> 26) & 0x07;
}
bool J1939Identifier::getDataPage()
{
    return (rawIdentifier >> 24) & 0x01;
}
uint8_t J1939Identifier::getPDUFormat()
{
    return (rawIdentifier >> 16) & 0xFF;
}
uint8_t J1939Identifier::getPDUSpecific()
{
    return (rawIdentifier >> 8) & 0xFF;
}
uint8_t J1939Identifier::getSourceAddress()
{
    return rawIdentifier & 0xFF;
}
uint32_t J1939Identifier::getPGN()
{
    if (getPDUFormat() < 240)
    {
        return ((getDataPage() << 16) & 0x10000) | ((getPDUFormat() << 8) & 0xff00);
    }
    else
    {
        return ((getDataPage() << 16) & 0x10000) | ((getPDUFormat() << 8) & 0xff00) | (getPDUSpecific() & 0xff);
    }
}
uint32_t J1939Identifier::getRawIdentifier()
{
    return rawIdentifier;
}