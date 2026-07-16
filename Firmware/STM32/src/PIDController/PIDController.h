#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H
class PIDController
{
private:
    float kP;
    float kD;
    float kI;
    float error;
    float lastError;
    float rawDerivative;
    float derivative;
    float output;
    float integralSum;

public:
    float getKp();
    void setKp(float);
    float getKd();
    void setKd(float);
    float getKi();
    void setKi(float);
    float computeError(float, float);
    void saveLastError();
    float computeDerivative();
    float computeIntegral(float);
    float computeOutput();
    float getOutput();
    void update(float, float, float);
    float computeRawDerivative(float);
    float getLastError();
    float getError();
};
#endif