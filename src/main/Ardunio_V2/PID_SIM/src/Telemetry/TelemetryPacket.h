#ifndef TELEMETRYPACKET
#define TELEMETRYPACKET
#include <Arduino.h>
class TelemetryPacket
{
private:
        double target;
        double error;
        double lastError;
        double position;
        double kP;
        double kI;
        double kD;
        double percentComplete;
        double output;

public:
        void setTarget(double);
        void setError(double);
        void setLastError(double);
        void setPosition(double);
        void setKP(double);
        void setKI(double);
        void setKD(double);
        void setPercentComplete(double);
        void setOutput(double);
        String toString();
};
#endif