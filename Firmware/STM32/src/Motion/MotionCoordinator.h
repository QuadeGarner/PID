#ifndef MOTIONCONTROLLER
#define MOTIONCONTROLLER
#include "../VirtualMotor/VirtualMotor.h"
#include "../Telemetry/TelemetryPacket.h"
#include "../Telemetry/TelemetryManager.h"
#include "../PIDController/PIDCOntroller.h"
class MotionCoordinator
{
private:
    double target;
    static double home;
    double time = 0;
    double lastTime = 0;
    PIDController controller;
    VirtualMotor vm;
    TelemetryManager tm;
    double power;

public:
    double getTarget();
    double getHome();
    double getPower();
    double getTime();
    double getPosition();
    void setTarget(double);
    double getCycleTime();
    void setTime(double);
    void setHome(double);
    void setPower(double);
    void setLastTime(double);
    void run();
    MotionCoordinator(TelemetryManager, VirtualMotor, PIDController);
    void updatePIDController(double, double, double);
    TelemetryPacket createPacket();
    double computePercentComplete(double, double);
};
#endif