#ifndef CONTROLLER_H
#define CONTROLLER_H
class Controler{
private:
    double kP;
    double kD;
    double error;
    double lastError;
    double target;
    double currentPosition;
    double rawDerviative;
    double derviative;
    double power;
    double dd_t;
public:
    double getKp();
    void setKp(double);
    double getKd();
    void setKd(double);
    double computeError();
    double saveLastError();
    double getTarget();
    double getCurrentPosition();
    void setCurrentPosition(double);
    void setTarget(double);
    double computerRawDerviative();
    double computeDerviative();
    double computePower();
};
#endif