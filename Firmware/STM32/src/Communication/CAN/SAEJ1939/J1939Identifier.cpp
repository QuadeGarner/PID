#include "J1939Identifier.h"
J1939Identifier::J1939Identifier(uint8_t p, bool r, bool dp, uint8_t pf, uint8_t ps, DeviceID sa)
{
    rawIdentifier = ((p & 0x07) << 26) | ((r & 0x01) << 25) | ((dp & 0x01) << 24) | ((pf) << 16) | (ps << 8) | static_cast<uint8_t>(sa);
}
J1939Identifier::J1939Identifier(uint32_t messageID)
{
    rawIdentifier = (messageID & 0x1FFFFFFF);
}
J1939Identifier::J1939Identifier()
{
    rawIdentifier = 0;
}
uint8_t J1939Identifier::getPriority() const
{
    return (rawIdentifier >> 26) & 0x07;
}
bool J1939Identifier::getDataPage() const
{
    return (rawIdentifier >> 24) & 0x01;
}
uint8_t J1939Identifier::getPDUFormat() const
{
    return (rawIdentifier >> 16) & 0xFF;
}
uint8_t J1939Identifier::getPDUSpecific() const
{
    return (rawIdentifier >> 8) & 0xFF;
}
uint8_t J1939Identifier::getSourceAddress() const
{
    return rawIdentifier & 0xFF;
}
uint32_t J1939Identifier::getPGN() const
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
uint32_t J1939Identifier::getRawIdentifier() const
{
    return rawIdentifier;
}
bool J1939Identifier::getReserved()
{
    return (rawIdentifier >> 25) & 0x01;
}