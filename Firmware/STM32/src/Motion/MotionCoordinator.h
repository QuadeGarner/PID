#ifndef MOTIONCONTROLLER
#define MOTIONCONTROLLER
#include "../src/MotorController/VitrualMotor/VirtualMotor.h"
#include "../Telemetry/TelemetryManager.h"
#include "../PIDController/PIDCOntroller.h"
#include "../Communication/CAN/IMessageReceiver.h"
#include "../Communication/CAN/CanNode.h"
class MotionCoordinator : public IMessageReceiver
{
private:
    float target;
    static float home;
    float time = 0;
    float lastTime = 0;
    PIDController controller;
    TelemetryManager tm;
    float power;
    CanNode cn;
    uint32_t tickCount;
    // Non absolute values, absloute values are in the Vitural motor class
    float motorPosition = 0.0f;
    float motorVelocity = 0.0f;

public:
    float getTarget();
    float getHome();
    float getPower();
    float getTime();
    void setTarget(float);
    float getCycleTime();
    void setTime(float);
    void setHome(float);
    void setPower(float);
    void setLastTime(float);
    void run();
    MotionCoordinator(TelemetryManager, PIDController, CanBusManager &);
    void updatePIDController(float, float, float);
    TelemetryPacket createPacket();
    float computePercentComplete(float, float);
    void receive(const CAN_Message &) override;
    CAN_Frame createSyncFrame();
    CAN_Frame createPIDFrame();
    CAN_Frame createMotorFrame();
    void updateTickCount();
};
#endif