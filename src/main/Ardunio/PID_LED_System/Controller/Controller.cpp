#include "Controller.h"


double Controller:: getKp(){return kP;}
void Controller::setKp(double kP){this ->kP = kP;}
double Controller::getKd(){return kD;}
void Controller::setKd(double kD){this->kD=kD;}
double Controller::computeError(){
    this ->error = this->getTarget() - this ->getCurrentPosition();
    return error;
}
double Controller::saveLastError(){lastError = error;}
double Controller::getTarget(){return target;}
void Controller::setTarget(double target){this-> target = target; }
double Controller:: computeRawDerviative(){
    this-> rawDerviative = (this->computeError() - lastError )/ this->getDD_T();
    return rawDerviative;
}
double Controller::computeDerviative(){
    this -> derviative = (.1 * rawDerviative) + (.9 * derviative);
    return derviative;
}
double Controller:: getPower(){
    return power;
}
double Controller::computePower(){
    this-> power = (error * this->getKp()) + (derviative * this->getKd());
    if(power > 1.0 ){
      power = 1.0;
    }
    if(power < -1.0){
      power = -1.0;
    }
    if( power < 0.05 && power > 0) {
      power = 0.05;
    }else if( power > -0.05 && power < 0){
      power = -.05;
    }
    return power;
}
double Controller:: getCurrentPosition(){return currentPosition;}
void Controller:: setCurrentPosition(double currentPosition){this->currentPosition = currentPosition;}
void Controller :: setDD_T(double dd_t){this-> dd_t = dd_t;}
double Controller:: getDD_T(){return dd_t;}
double Controller:: getLastError(){
  return lastError;
}
void Controller::update(){
    this -> computeError();
    this-> computeRawDerviative();
    this -> saveLastError();
    this -> computeDerviative();
    this -> computePower();
}