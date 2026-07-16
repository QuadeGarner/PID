#include "TelemetryPacket.h"
void TelemetryPacket::setTarget(float target)
{
    this->target = target;
}
void TelemetryPacket::setError(float error)
{
    this->error = error;
}
void TelemetryPacket::setLastError(float lastError)
{
    this->lastError = lastError;
}
void TelemetryPacket::setPosition(float position)
{
    this->position = position;
}
void TelemetryPacket::setKP(float kp)
{
    this->kP = kp;
}
void TelemetryPacket::setKI(float ki)
{
    this->kI = ki;
}
void TelemetryPacket::setKD(float kd)
{
    this->kD = kd;
}
void TelemetryPacket::setPercentComplete(float percentComplete)
{
    this->percentComplete = percentComplete;
}
void TelemetryPacket::setOutput(float output)
{
    this->output = output;
}
String TelemetryPacket::toString()
{
    return (String)target + "," + (String)error + "," + (String)lastError + "," + (String)position + ","

           + (String)kP + "," + (String)kI + "," + (String)kD + "," + (String)percentComplete + "," + (String)output + "\n";
}