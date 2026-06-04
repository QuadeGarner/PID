#include "PACKET.h"
void Packet::setKP(double field1){
    this->kP = field1;
}
void Packet::setKI(double field2){
    this ->kI = field2;
}
void Packet::setKD(double field3){
    this -> kD = field3;
}
void Packet::setCompletionTime(long time){
    this-> completionTime = time;
}
double Packet::getKP(){
    return kP;
}
double Packet::getKI(){
    return kI;
}
double Packet::getKD(){
    return kD;
}
long Packet::getCompletionTime(){
    return completionTime;
}
void Packet:: setStartTime(){
    this-> startTime = millis();
}
long Packet::getStartTime(){
    return startTime;
}
void Packet::setStatus(PacketStatus status){
    this->status = status;
}
void Packet::setCompletionStatus(PacketCompletionStatus status){
    this->completionStatus = status;
}
