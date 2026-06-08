#include "PIDController.h"


double PIDController:: getKp(){return kP;}
void PIDController::setKp(double kP){this ->kP = kP;}
double PIDController::getKd(){return kD;}
void PIDController::setKd(double kD){this->kD=kD;}
double PIDController::getKi(){return kI;}
void PIDController::setKi(double kI){this -> kI=kI;}
double PIDController::computeError(double target, double currentPosition){
    this-> error = target - currentPosition;
    return error;
}
void PIDController::saveLastError(){lastError = error;}
double PIDController:: computeRawDerivative(double dd_t){
    if( dd_t <= 0 ){
        return derivative;
    }
    this-> rawDerivative = (error - lastError )/ dd_t;
    return rawDerivative;
}
double PIDController::computeDerivative(){
    this -> derivative = (.1 * rawDerivative) + (.9 * derivative);
    return derivative;
}
double PIDController::computeIntegral(double dd_t){
    this -> integralSum += error * dd_t;
    if(integralSum > 100){
        integralSum = 100;
    }
    if (integralSum < -100){
        integralSum = -100;
    }
    return integralSum;
}
double PIDController:: getOutput(){
    return output;
}
double PIDController::computeOutput(){
    this-> output = (error * this->getKp()) +(integralSum * this->getKi())+ (derivative * this->getKd());
    return output;
}

double PIDController:: getLastError(){
  return lastError;
}
void PIDController::update(double target, double currentPosition, double dd_t){
    this -> computeError(target, currentPosition);
    this-> computeRawDerivative(dd_t);
    this -> computeIntegral(dd_t);
    this -> saveLastError();
    this -> computeDerivative();
    this -> computeOutput();
}
