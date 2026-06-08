#include "MotionCoordinator.h"
#include <Arduino.h>
double MotionCoordinator::getTarget()
{
    return target;
}
void MotionCoordinator::setTarget(double target)
{
    this->target = target;
}
double MotionCoordinator::getPosition()
{
    return vm.getPosition();
}
double MotionCoordinator::getHome()
{
    return home;
}
double MotionCoordinator::getTime()
{
    return time;
}
void MotionCoordinator::setHome(double home)
{
    this->home = home;
}
void MotionCoordinator::setTime(double time)
{
    this->time = time / 1000;
}
void MotionCoordinator::setPower(double power)
{
    this->power = power;

    if (power < 0.05 && power > -0.05)
    {
        this->power = 0;
    }

    if (power > 1)
    {
        this->power = 1;
    }
    else if (power < -1)
    {
        this->power = -1;
    }
}
double MotionCoordinator::getPower()
{
    return power;
}
MotionCoordinator::MotionCoordinator(TelemetryManager tm, VirtualMotor vm, PIDController pc) : vm(vm), tm(tm), controller(pc) {}
void MotionCoordinator::run()
{
    // SerialManager and PacketParser are not part of the MotionControl
    setTime((double)millis());
    controller.update(target, vm.getPosition(), getCycleTime());
    setPower(controller.getOutput());
    vm.update(getPower(), getCycleTime());
    TelemetryPacket tp = createPacket();
    static unsigned long lastTelemetry = 0;

    if (millis() - lastTelemetry > 1000)
    {
        tm.sendMessage(createPacket());
        lastTelemetry = millis();
    }
    setLastTime(getTime());
}
void MotionCoordinator::setLastTime(double time)
{
    this->lastTime = time;
}
double MotionCoordinator::getCycleTime()
{
    return time - lastTime;
}
void MotionCoordinator::updatePIDController(double kp, double ki, double kd)
{
    controller.setKp(kp);
    controller.setKd(kd);
    controller.setKi(ki);
}
TelemetryPacket MotionCoordinator::createPacket()
{
    TelemetryPacket tp;
    tp.setTarget(getTarget());
    tp.setError(controller.getError());
    tp.setKD(controller.getKd());
    tp.setKP(controller.getKp());
    tp.setKI(controller.getKi());
    tp.setPosition(getPosition());
    tp.setLastError(controller.getLastError());
    tp.setPercentComplete(computePercentComplete(getPosition(), getTarget()));
    tp.setOutput(getPower());
    return tp;
}
double MotionCoordinator::computePercentComplete(double pos, double tar)
{
    double const baseOffset = 100;
    double const safeOffset = 1;
    double percentComplete = 0;
    if (tar - baseOffset > 0 && tar - baseOffset < 1)
    {
        percentComplete = (pos - safeOffset) / (tar - safeOffset) * 100;
    }
    else
    {
        percentComplete = (pos - baseOffset) / (tar - baseOffset) * 100;
    }
    percentComplete = fabs(percentComplete);
    return percentComplete;
}