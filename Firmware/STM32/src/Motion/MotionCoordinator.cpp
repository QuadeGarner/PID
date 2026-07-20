#include "MotionCoordinator.h"
#include <Arduino.h>
#include "../Librays/CanCodec.h"
float MotionCoordinator::getTarget()
{
    return target;
}
void MotionCoordinator::setTarget(float target)
{
    this->target = target;
}

float MotionCoordinator::getHome()
{
    return home;
}
float MotionCoordinator::getTime()
{
    return time;
}
void MotionCoordinator::setHome(float home)
{
    this->home = home;
}
void MotionCoordinator::setTime(float time)
{
    this->time = time / 1000;
}
void MotionCoordinator::setPower(float power)
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
float MotionCoordinator::getPower()
{
    return power;
}
MotionCoordinator::MotionCoordinator(TelemetryManager tm, PIDController pc, CanBusManager &bus) : tm(tm), controller(pc), cn(DeviceID::MOTION_COORDINATOR, bus, *this) {}
void MotionCoordinator::run()
{
    // SerialManager and PacketParser are not part of the MotionControl
    setTime((float)millis());
    tickCount++;
    cn.send(createSyncFrame());
    cn.send(createPIDFrame());
    TelemetryPacket tp = createPacket();
    static unsigned long lastTelemetry = 0;

    if (millis() - lastTelemetry > 1000)
    {
        tm.sendMessage(createPacket());
        lastTelemetry = millis();
    }
    setLastTime(getTime());
}
void MotionCoordinator::setLastTime(float time)
{
    this->lastTime = time;
}
float MotionCoordinator::getCycleTime()
{
    return time - lastTime;
}
void MotionCoordinator::updatePIDController(float kp, float ki, float kd)
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
float MotionCoordinator::computePercentComplete(float pos, float tar)
{
    float const baseOffset = 100;
    float const safeOffset = 1;
    float percentComplete = 0;
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
void MotionCoordinator::receive(CAN_Frame &frame)
{
    switch (frame.id)
    {
    case MOTOR_STATUS:
        // Create helper function to make more readabilty
        motorPosition = CanCodec::decodeFloat(frame, 0);
        motorVelocity = CanCodec::decodeFloat(frame, 4);
        break;
    case ENCODER_STATUS:
        // Create helper function to make more readabilty
        Serial.print("Encoder");
        break;
    case PID_STATUS:
        // Create helper function to make more readabilty
        Serial.print("PID");
        power = CanCodec::decodeFloat(frame, 0);
        CAN_Frame motorFrame{};
        motorFrame.id = MOTOR_COMMAND;
        motorFrame.dlc = 8;
        CanCodec::encodeFloat(motorFrame, 0, power);
        cn.send(motorFrame);
        break;
    case FAULTREPORT:
        // Create helper function to make more readabilty
        Serial.print("FAULT");
        break;

    default:
        break;
    }
}
CAN_Frame MotionCoordinator::createSyncFrame()
{
    CAN_Frame syncFrame{};
    syncFrame.id = CONTROL_SYNC;
    syncFrame.dlc = 8;
    CanCodec::encodeFloat(syncFrame, 0, time);
    CanCodec::encodeInt32(syncFrame, 4, tickCount);
    return syncFrame;
}
CAN_Frame MotionCoordinator::createPIDFrame()
{
    CAN_Frame pidFrame{};
    pidFrame.id = PID_COMMAND;
    pidFrame.dlc = 8;
    CanCodec::encodeFloat(pidFrame, 0, target);
    CanCodec::encodeFloat(pidFrame, 4 motorPosition);
    return pidFrame;
}