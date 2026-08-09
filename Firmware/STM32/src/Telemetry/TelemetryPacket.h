#pragma once
struct TelemetryPacket
{
        float target;
        float position;
        // float velocity;
        float kp;
        float ki;
        float kd;
        float percentComplete;
        float error;
        float output;
        float lastError;
};