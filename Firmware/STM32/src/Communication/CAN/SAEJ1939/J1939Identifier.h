#ifndef J1939IDENTIFER
#define J1939IDENTIFER
#include "../MotorCommand.h"
#include <cstdint>
class J1939Identifier
{
private:
    uint32_t rawIdentifier;

public:
    J1939Identifier(uint8_t, bool r, bool, uint8_t,
                    uint8_t, DeviceID);
    J1939Identifier(uint32_t);
    J1939Identifier();
    ~J1939Identifier() = default;
    uint8_t getPriority() const;
    bool getDataPage() const;
    uint8_t getPDUFormat() const;
    uint8_t getPDUSpecific() const;
    uint8_t getSourceAddress() const;
    uint32_t getPGN() const;
    uint32_t getRawIdentifier() const;
    bool getReserved();
};
#endif