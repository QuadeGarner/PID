#ifndef PACKET
#define PACKET
#include "../../Enums/PacketStatus.h"
#include "../../Enums/PacketCompletionStatus.h"
#include <Arduino.h>
class Packet
{
private:
    double target;
    double kP;
    double kI;
    double kD;
    long completionTime;
    long startTime;
    PacketStatus status;
    PacketCompletionStatus completionStatus;

public:
    void setTarget(double);
    double getTarget();
    void setKP(double);
    void setKI(double);
    void setKD(double);
    void setCompletionTime(long);
    double getKP();
    double getKI();
    double getKD();
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