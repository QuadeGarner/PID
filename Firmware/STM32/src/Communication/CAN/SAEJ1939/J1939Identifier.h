#ifndef J1939IDENTIFER
#define J1939IDENTIFER
#include <cstdint>
class J1939Identifier
{
private:
    uint32_t rawIdentifier = 0;

public:
    J1939Identifier(uint8_t,
                    bool, uint8_t,
                    uint8_t, uint8_t);
    J1939Identifier(uint32_t);
    ~J1939Identifier() = default;
    uint8_t getPriority();
    bool getDataPage();
    uint8_t getPDUFormat();
    uint8_t getPDUSpecific();
    uint8_t getSourceAddress();
    uint32_t getPGN();
    uint32_t getRawIdentifier();
};
#endif