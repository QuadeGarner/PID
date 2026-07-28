#ifndef MOTORCOMMANDPROTOCOL
#define MOTORCOMMANDPROTOCOL
class MotorCommandProtocol
{
public:
    static CAN_Message create(float power);
    static float getPower(const CAN_Message &);
};
#endif