#ifndef CONTROLLER_H
#define CONTROLLER_H
class Controller{
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
    double computeRawDerviative();
    double computeDerviative();
    double computePower();
    double getPower();
    void setDD_T(double);
    double getDD_T();
    void update();

};
#endif