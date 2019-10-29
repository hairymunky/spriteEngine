#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
private:
    Uint64 mFrameStart;
    double mDeltaTime;

public:
    Timer();
    ~Timer();

    /**
     * Resets the clock.
    */
    void reset();

    /**
     * deltaTime
     * Returns the time in milliseconds since this timer instance
     * was reset.
     * @return dt in ms
    */
    double deltaTime();
};

#endif