#include "VirtualMotor.h"

VirtualMotor::VirtualMotor(float position, double mass, double damping, double power_scaling) : position(position), MASS(mass), DAMPING(damping), POWER_SCALING(power_scaling) {}

void VirtualMotor::update(float inputPower, float delta_t)
{
    double force = (inputPower * POWER_SCALING) - (velocity * DAMPING);
    acceleration = force / MASS;
    velocity += (acceleration * delta_t);
    position += velocity * delta_t;
}
float const VirtualMotor::getPosition()
{
    return position;
}
float const VirtualMotor::getVelocity()
{
    return velocity;
}