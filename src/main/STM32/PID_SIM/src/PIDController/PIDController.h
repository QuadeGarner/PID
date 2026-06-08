#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H
class PIDController
{
private:
    double kP;
    double kD;
    double kI;
    double error;
    double lastError;
    double rawDerivative;
    double derivative;
    double output;
    double integralSum;

public:
    double getKp();
    void setKp(double);
    double getKd();
    void setKd(double);
    double getKi();
    void setKi(double);
    double computeError(double, double);
    void saveLastError();
    double computeDerivative();
    double computeIntegral(double);
    double computeOutput();
    double getOutput();
    void update(double, double, double);
    double computeRawDerivative(double);
    double getLastError();
    double getError();
};
#endif