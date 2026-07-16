#ifndef MOTIONCONTROLLER
#define MOTIONCONTROLLER
#include "../VirtualMotor/VirtualMotor.h"
#include "../Telemetry/TelemetryManager.h"
#include "../PIDController/PIDCOntroller.h"
#include "../Communication/CAN/ICanReceiver.h"
#include "../Communication/CAN/CanNode.h"
class MotionCoordinator : public ICanReceiver
{
private:
    float target;
    static float home;
    float time = 0;
    float lastTime = 0;
    PIDController controller;
    VirtualMotor vm;
    TelemetryManager tm;
    float power;
    CanNode cn;

public:
    float getTarget();
    float getHome();
    float getPower();
    float getTime();
    float getPosition();
    void setTarget(float);
    float getCycleTime();
    void setTime(float);
    void setHome(float);
    void setPower(float);
    void setLastTime(float);
    void run();
    MotionCoordinator(TelemetryManager, VirtualMotor, PIDController, CanBusManager &);
    void updatePIDController(float, float, float);
    TelemetryPacket createPacket();
    float computePercentComplete(float, float);
    void receive(CAN_Frame &) override;
};
#endif