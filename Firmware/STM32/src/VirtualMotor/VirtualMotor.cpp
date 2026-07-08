#include "VirtualMotor.h"

VirtualMotor::VirtualMotor(double position, double mass, double damping, double power_scaling):
position(position),MASS(mass),DAMPING(damping), POWER_SCALING(power_scaling){}

void VirtualMotor::update(double inputPower, double delta_t){
    double force = (inputPower *POWER_SCALING) - (velocity * DAMPING);
    acceleration = force / MASS;
    velocity += (acceleration * delta_t);
    position += velocity * delta_t;
}
double const VirtualMotor::getPosition(){
    return position;
}
double const VirtualMotor::getVelocity(){
    return velocity;
}