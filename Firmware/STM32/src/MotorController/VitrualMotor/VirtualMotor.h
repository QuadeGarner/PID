#ifndef VIRTUAL_MOTOR_H
#define VIRTUAL_MOTOR_H
class VirtualMotor
{
private:
    float position;
    float velocity = 0;
    double acceleration = 0;
    double MASS;
    double DAMPING;
    double POWER_SCALING;

public:
    VirtualMotor(float, double, double, double);
    void update(float, float);
    float const getPosition();
    float const getVelocity();
};
#endif
