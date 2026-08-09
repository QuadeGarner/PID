#include "SimulationClock.h"
void SimClock::update()
{
    this->lastTime = time;
    this->time = millis() / 1000.0f;
    tick++;
}
float SimClock::getLastTime() const
{
    return lastTime;
}
uint32_t SimClock::getTickCount() const
{
    return tick;
}
float SimClock::getTime() const
{
    return time;
}
float SimClock::getDeltaTime() const
{
    return time - lastTime;
}