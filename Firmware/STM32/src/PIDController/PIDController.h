#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H
#include "../Communication/CAN/IMessageReceiver.h"
#include "../Communication/Protocol/PIDStatusProtocol.h"
#include "../Communication/Protocol/ControlSyncProtocol.h"
#include "../Communication/CAN/Transport/CommunicationManager.h"
#include "../Communication/Protocol/PIDUpdateProtocol.h"
#include "../Communication/Protocol/PIDCommand.h"
#include <cstdint>
class PIDController : public IMessageReceiver
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
    CommunicationManager cm;
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
    void receiveMessage(const CAN_Message &) override;
    PIDController(CanBusManager &);
};
#endif