#include "Packet.h"
void Packet::setTarget(float target)
{
    this->target = target;
}
void Packet::setKP(float field1)
{
    this->kP = field1;
}
void Packet::setKI(float field2)
{
    this->kI = field2;
}
void Packet::setKD(float field3)
{
    this->kD = field3;
}
void Packet::setCompletionTime(long time)
{
    this->completionTime = time;
}
float Packet::getTarget()
{
    return target;
}
float Packet::getKP()
{
    return kP;
}
float Packet::getKI()
{
    return kI;
}
float Packet::getKD()
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