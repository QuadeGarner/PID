#ifndef CONVERTER
#define CONVERTER
#include "./Transport.h"
#include "../CanFrame.h"
class Converter
{
public:
    static CAN_Frame convertToFrame(const CAN_Message &);
    static CAN_Message convertToMessage(const CAN_Frame &);
};
#endif