#pragma once
#include <stdint.h>
#include "Arduino.h"
class SimClock
{
private:
    float time = 0;
    float lastTime = 0;
    uint32_t tick = 0;

public:
    void update();
    float getTime() const;
    float getLastTime() const;
    uint32_t getTickCount() const;
    float getDeltaTime() const;
};