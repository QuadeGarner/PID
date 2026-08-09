#include "MotionPlanner.h"
void MotionPlanner::setTarget(float target)
{
    this->target = target;
}
float MotionPlanner::getTarget() const
{
    return target;
}
float MotionPlanner::computePercentComplete(float pos) const
{
    if (target == 0.0f)
    {
        return 0.0f;
    }
    return pos / target * 100;
}
