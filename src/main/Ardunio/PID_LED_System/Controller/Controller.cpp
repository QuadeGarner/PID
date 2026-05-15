#include "Controller.h"


double Controller:: getKp(){return kP;}
void Controller::setKp(double kP){this ->kP}
double Controller::getKd(){return kD;}
void Controller::setKd(double kD){this-> kD;}
double Controller::getError(){}
double Controller::getLastError(){}
double Controller::getTarget(){return target;}
void Controller::setTarget(double target){this-> target;}
double Controller::getDerivate(){}
double Controller::getPower(){}