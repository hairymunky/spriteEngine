#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
private:
    Uint64 mCurrentTime;
    Uint64 mLastTime;

public:
    Timer();
    ~Timer();

    /**
     * Resets the clock.
    */
    void reset();

    /**
     * Ticks the clock
     * @return Uint64 the current timestamps for those who need to know
    */
    Uint64 getCurrent();

    /**
     * deltaTime
     * Returns the difference in milliseconds between the current and last
     * timestamps.
     * @return double in ms
    */
    double deltaTime();
};


#endif