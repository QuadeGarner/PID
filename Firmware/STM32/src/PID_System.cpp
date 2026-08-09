#include "./Motion/MotionCoordinator.h"
#include "./Communication/Packet/PacketPaser.h"
#include "./Communication/Serial/SerialManager.h"
#include "./PIDController/PIDController.h"
#include "./Communication/CAN/CanBusManager.h"
#include "./Motion/MotionPlanner.h"
#include "./Timing/SimulationClock.h"
#include <math.h>
#include <Arduino.h>

int const potPin = A0;
int const portKP = A1;
int const portKD = A3;
CanBusManager bus;
VirtualMotor vm = VirtualMotor(double(101), double(1.0), 0.1, double(5));
PIDController pd = PIDController(bus);
TelemetryManager tm;
MotionPlanner mp;
SimClock sm;
MotionCoordinator mc = MotionCoordinator(mp, sm, bus);

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    mc.run();
}
