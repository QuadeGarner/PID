#pragma once
class MotionPlanner
{
private:
    float target;

public:
    void setTarget(float);
    float getTarget() const;
    float computePercentComplete(float) const;
};