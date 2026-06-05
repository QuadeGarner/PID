#include "MOTIONCOORDINATOR.h"
double MotionCoordinator::getTarget(){
    return target;
}
double MotionCoordinator::getPositon(){
    return vm.getPosition();
}
double getHome(){
    return home;
}
double MotionCoordinator::getTime(){
    return time;
}
static void MotionCoordinator::setHome(double home){
    this-> home = home;
}
void MotionCoordinator::setTime(double time){
    this-> time = time / 1000;
}
void MotionCoordinator::setPower(double power){
    this->power = power;
    //if statement clamping power
    if( power< 0.05 && power > -0.05) {
        this-> power = 0
    }
}
double MotionCoordinator:: getPower(){
    return power;
}
MotionCoordinator::MotionCoordinator(TelemetryManger tm, VirualMotor vm, PIDController pc):vm(vm),tm(tm)controller(pc);
void MotionCoordinator::run(){
    // SerialManager and PacketParser are not part of the MotionControl
    setTime((double)millis());
    pc.update(target, vm.getPositon(), getCycleTime());
    setPower(pc.getOutput());
    vm.update(getPower(), getCycleTime());
    tm.sendMessage(createPacket());
    setLastTime(getTime());
}
void MotionCoorndator::setLastTime(double time){
    this->lastTime = time ;
}
double MotionCoordinator::getCycleTime(){
    return time - lastTime;
}
void MotionController:: updatePIDController(double kp, double ki, double kd){
    pc.setKP(kp);
    pc.setKD(kd);
    pc.setKI(ki);
}