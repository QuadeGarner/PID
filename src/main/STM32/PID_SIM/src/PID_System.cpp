#include "./Motion/MotionCoordinator.h"
#include "./Communication/Packet/PacketPaser.h"
#include "./Communication/Serial/SerialManager.h"
#include "./PIDController/PIDController.h"
#include <math.h>
#include <Arduino.h>

int const potPin = A0;
int const portKP = A1;
int const portKD = A3;
VirtualMotor vm = VirtualMotor(double(101), double(1.0), 0.1, double(5));
PIDController pd;
TelemetryManager tm;
MotionCoordinator mc = MotionCoordinator(tm, vm, pd);
SerialManager sm;
PacketParser pp;
Packet p;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    if (sm.isAvaiable())
    {
        p = pp.createPacket(sm.getData());
    }
    if (p.getPacketCompletionStatus() == PacketCompletionStatus::VALID_COMPLETION_TIME && p.getPacketStatus() == PacketStatus::VALID)
    {
        mc.setTarget(p.getTarget());
        mc.updatePIDController(p.getKP(), p.getKI(), p.getKD());
        p.clearData();
        }
    mc.run();
}
