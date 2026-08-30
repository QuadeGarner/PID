#include "MotionCoordinator.h"
#include <Arduino.h>
#include "../Librays/CanCodec.h"

float MotionCoordinator::getHome()
{
    return home;
}
void MotionCoordinator::setHome(float home)
{
    this->home = home;
}

MotionCoordinator::MotionCoordinator(MotionPlanner &mp, SimClock &sm, CanBusManager &bus) : mp(mp), sc(sc), cm(DeviceID::MOTION_COORDINATOR, bus, *this) {}
void MotionCoordinator::run()
{
    if (serial.isAvaiable())
    {
        Packet packet = parser.createPacket(serial.getData());
        if (packet.getPacketStatus() == PacketStatus::VALID)
        {
            mp.setTarget(packet.getTarget());
            cm.send(PIDUpdateProtocol::create(packet.getKP(), packet.getKI(), packet.getKD()));
            tp.kp = packet.getKP();
            tp.kd = packet.getKD();
            tp.ki = packet.getKI();
            tp.target = packet.getTarget();
        }
    }
    // Send a Control Sync every loop
    sc.update();
    cm.send(ControlSyncProtocol::create(sc.getTime(), sc.getTickCount()));
    //
    cm.send(PIDCommandProtocol::create(mp.getTarget(), motorPosition));
    tp.percentComplete = mp.computePercentComplete(motorPosition);
    telemetry.sendMessage(tp);
}

void MotionCoordinator::receiveMessage(const CAN_Message &message)
{
    switch (message.identifier)
    {
    case MOTOR_STATUS:
        motorPosition = MotorStatusProtocol::getPosition(message);
        tp.position = motorPosition;
        break;
    case ENCODER_STATUS:
        break;
    case PID_STATUS:
        output = PidStatusProtocol::getOutput(message);
        tp.error = PidStatusProtocol::getError(message);
        tp.lastError = PidStatusProtocol::getLastError(message);
        tp.output = output;
        cm.send(MotorCommandProtocol::create(output));
        break;
    case FAULTREPORT:
        break;
    default:
        break;
    }
}