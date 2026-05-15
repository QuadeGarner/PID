#ifndef CONTROLLER_H
#define CONTROLLER_H
class Controler{
private:
    double kP;
    double kD;
    double error;
    double lastError;
    double target;
    double derivate;
    double power;
    long currentTime;
    long lastTime;
    long delta_t;
    double dd_t;
public:
    double getKp();
    void setKp(double);
    double getKd();
    void setKd(double);
    double getError();
    double getLastError();
    double getTarget();
    void setTarget(double);
    double getDerivate();
    double getPower();
};
#endif