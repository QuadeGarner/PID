#ifndef MOTIONCONTROLLER
#define MOTIONCONTROLLER
#include "VituralMotor.h"
#include "TelemetryPacket.h"
#include "TelemetryManager.h"
#include "PIDController.h"
class{
    private:
        double target;
        static double home;
        double time = 0;
        double lastTime = 0;
        PIDController controller;
        VituralMotor vm;
        TelemetryManager tm;

    public:
        double getTarget();
        double getHome();
        double getPower();
        double getTime();
        void setLastTime(double);
        void setTarget(double);
        double getCycleTime();
        void setTime();
        static void setHome(double);
        void setPower(double);
        void run();
        MotionCoordinator(TelemetryManager, VituralMotor, PIDController);
};
#endif