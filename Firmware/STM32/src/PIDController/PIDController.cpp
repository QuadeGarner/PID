#include "PIDController.h"

float PIDController::getKp() { return kP; }
void PIDController::setKp(float kP) { this->kP = kP; }
float PIDController::getKd() { return kD; }
void PIDController::setKd(float kD) { this->kD = kD; }
float PIDController::getKi() { return kI; }
void PIDController::setKi(float kI) { this->kI = kI; }
float PIDController::computeError(float target, float currentPosition)
{
    this->error = target - currentPosition;
    return error;
}
void PIDController::saveLastError() { lastError = error; }
float PIDController::computeRawDerivative(float dd_t)
{
    if (dd_t <= 0)
    {
        return derivative;
    }
    this->rawDerivative = (error - lastError) / dd_t;
    return rawDerivative;
}
float PIDController::computeDerivative()
{
    this->derivative = (.1 * rawDerivative) + (.9 * derivative);
    return derivative;
}
float PIDController::computeIntegral(float dd_t)
{
    this->integralSum += error * dd_t;
    if (integralSum > 100)
    {
        integralSum = 100;
    }
    if (integralSum < -100)
    {
        integralSum = -100;
    }
    return integralSum;
}
float PIDController::getOutput()
{
    return output;
}
float PIDController::computeOutput()
{
    this->output = (error * this->getKp()) + (integralSum * this->getKi()) + (derivative * this->getKd());
    return output;
}

float PIDController::getLastError()
{
    return lastError;
}
float PIDController::getError()
{
    return error;
}
void PIDController::update(float target, float currentPosition, float dd_t)
{
    this->computeError(target, currentPosition);
    this->computeRawDerivative(dd_t);
    this->computeIntegral(dd_t);
    this->saveLastError();
    this->computeDerivative();
    this->computeOutput();
}
