#ifndef PACKET
#define PACKET
#include "../../Enums/PacketStatus.h"
#include "../../Enums/PacketCompletionStatus.h"
#include <Arduino.h>
class Packet
{
private:
    float target;
    float kP;
    float kI;
    float kD;
    long completionTime;
    long startTime;
    PacketStatus status;
    PacketCompletionStatus completionStatus;

public:
    void setTarget(float);
    float getTarget();
    void setKP(float);
    void setKI(float);
    void setKD(float);
    void setCompletionTime(long);
    float getKP();
    float getKI();
    float getKD();
    long getCompletionTime();
    void setStartTime();
    long getStartTime();
    PacketStatus getPacketStatus();
    void setStatus(PacketStatus);
    PacketCompletionStatus getPacketCompletionStatus();
    void setPacketCompletionStatus(PacketCompletionStatus);
    void clearData();
};
#endif