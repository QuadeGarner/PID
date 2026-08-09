#ifndef MOTIONCONTROLLER
#define MOTIONCONTROLLER
#include "../src/MotorController/VitrualMotor/VirtualMotor.h"
#include "../Telemetry/TelemetryManager.h"
#include "../PIDController/PIDCOntroller.h"
#include "../Communication/CAN/IMessageReceiver.h"
#include "../Communication/CAN/CanNode.h"
#include "./Communication/Protocol/protocol.h"
#include "./Communication/Packet/Packet.h"
#include "./Communication/Packet/PacketPaser.h"
#include "./Communication/Serial/SerialManager.h"
#include "./Timing/SimulationClock.h"
#include "MotionPlanner.h"

class MotionCoordinator : public IMessageReceiver
{
private:
    static float home;
    CommunicationManager cm;
    MotionPlanner mp;
    SimClock sc;
    TelemetryManager telemetry;
    UARTParser parser;
    SerialManager serial;
    TelemetryPacket tp{};
    // Non absolute values, absloute values are in the Vitural motor class
    float motorPosition = 0.0f;
    float motorVelocity = 0.0f;
    float output;

public:
    float getHome();
    void setHome(float);
    void run();
    MotionCoordinator(MotionPlanner &, SimClock &, CanBusManager &);
    void receiveMessage(const CAN_Message &) override;
};
#endif