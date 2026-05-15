#ifndef VIRTUAL_MOTOR_H
#define VIRTUAL_MOTOR_H
class VirtualMotor{
private:
    double position;
    double velocity = 0;
    double acceleration = 0;
    double MASS ;
    double DAMPING;
    double POWER_SCALING;
public:
    VirtualMotor(double, double, double,double);
    void update(double, double);
    double const getPosition();
    double const getVelocity();
};
#endif
