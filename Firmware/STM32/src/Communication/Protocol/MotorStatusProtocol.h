#ifndef MOTORSTATUSPROTOCOL
#define MOTORSTATUSPROTOCOL
class MotorStatusProtocol
{
public:
    static CAN_Message create(float position, float velocity);
    static float getPosition(const CAN_Message &);
    static float getVelocity(const CAN_Message &);
};
#endif