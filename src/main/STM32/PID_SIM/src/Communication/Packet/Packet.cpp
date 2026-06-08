#include "Packet.h"
void Packet::setTarget(double target)
{
    this->target = target;
}
void Packet::setKP(double field1)
{
    this->kP = field1;
}
void Packet::setKI(double field2)
{
    this->kI = field2;
}
void Packet::setKD(double field3)
{
    this->kD = field3;
}
void Packet::setCompletionTime(long time)
{
    this->completionTime = time;
}
double Packet::getTarget()
{
    return target;
}
double Packet::getKP()
{
    return kP;
}
double Packet::getKI()
{
    return kI;
}
double Packet::getKD()
{
    return kD;
}
long Packet::getCompletionTime()
{
    return completionTime;
}
void Packet::setStartTime()
{
    this->startTime = millis();
}
long Packet::getStartTime()
{
    return startTime;
}
void Packet::setStatus(PacketStatus status)
{
    this->status = status;
}
void Packet::setPacketCompletionStatus(PacketCompletionStatus status)
{
    this->completionStatus = status;
}
PacketStatus Packet::getPacketStatus()
{
    return status;
}
PacketCompletionStatus Packet::getPacketCompletionStatus()
{
    return completionStatus;
}
void Packet::clearData()
{
    setTarget(0);
    setKP(0);
    setKI(0);
    setKD(0);
    setPacketCompletionStatus(PacketCompletionStatus::INVALID_NO_DATA);
    setStatus(PacketStatus::PACKET_USED);
    setStartTime();
    setCompletionTime(0);
}