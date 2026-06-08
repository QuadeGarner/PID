#include "MotionCoordinator.h"
#include "PacketPaser.h
#include "SerialManager.h"
#include <math.h>

int const potPin = A0;
int const portKP = A1;
int const portKD = A3;
VirtualMotor vm = VirtualMotor(double(101),double(1.0),0.1,double(5));
PIDContoller pd ;
TelemetryManager tm;
MotionCoordinator mc;
SerialManager sm;
PacketParser pp;
Packet p;


void setup() {
    mc = MotionCoordinator(tm, vm, pd);
}

void loop() {
    if(sm.isAvaiable()){
        p = pp.createPacket(sm.getData());
    }
    if( p.getCompletionStatus() == PacketCompletionStatus::VALID_COMPLETION_TIME
    && p.getPacketStatus() == PacketStatus::VALID){
        mc.updatePIDController(p.getKP(), p.getKI(). p.getKD());
        p.clearData();
    }
    mc.run();
}

