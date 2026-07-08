#include "TelemetryPacket.h"
void TelemetryPacket::setTarget(double target)
{
    this->target = target;
}
void TelemetryPacket::setError(double error)
{
    this->error = error;
}
void TelemetryPacket::setLastError(double lastError)
{
    this->lastError = lastError;
}
void TelemetryPacket::setPosition(double position)
{
    this->position = position;
}
void TelemetryPacket::setKP(double kp)
{
    this->kP = kp;
}
void TelemetryPacket::setKI(double ki)
{
    this->kI = ki;
}
void TelemetryPacket::setKD(double kd)
{
    this->kD = kd;
}
void TelemetryPacket::setPercentComplete(double percentComplete)
{
    this->percentComplete = percentComplete;
}
void TelemetryPacket::setOutput(double output)
{
    this->output = output;
}
String TelemetryPacket::toString()
{
    return (String)target + "," + (String)error + "," + (String)lastError + "," + (String)position + ","

           + (String)kP + "," + (String)kI + "," + (String)kD + "," + (String)percentComplete + "," + (String)output + "\n";
}