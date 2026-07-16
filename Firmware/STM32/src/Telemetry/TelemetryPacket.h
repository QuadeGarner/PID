#ifndef TELEMETRYPACKET
#define TELEMETRYPACKET
#include <Arduino.h>
class TelemetryPacket
{
private:
        float target;
        float error;
        float lastError;
        float position;
        float kP;
        float kI;
        float kD;
        float percentComplete;
        float output;

public:
        void setTarget(float);
        void setError(float);
        void setLastError(float);
        void setPosition(float);
        void setKP(float);
        void setKI(float);
        void setKD(float);
        void setPercentComplete(float);
        void setOutput(float);
        String toString();
};
#endif