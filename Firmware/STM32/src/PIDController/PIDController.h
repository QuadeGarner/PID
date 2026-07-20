#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H
#include "../Communication/CAN/ICanReceiver.h"
#include <cstdint>
class PIDController : public ICanReceiver
{
private:
    float kP;
    float kD;
    float kI;
    float error;
    float lastError;
    float rawDerivative;
    float derivative;
    float output;
    float integralSum;
    float currentTime;
    float lastTime;
    uint32_t tickCount;
    float getComputetime();

public:
    float getKp();
    void setKp(float);
    float getKd();
    void setKd(float);
    float getKi();
    void setKi(float);
    float computeError(float, float);
    void saveLastError();
    float computeDerivative();
    float computeIntegral(float);
    float computeOutput();
    float getOutput();
    void update(float, float, float);
    float computeRawDerivative(float);
    float getLastError();
    float getError();
    void receive(CAN_Frame &) override;
};
#endif