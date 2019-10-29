#include "timer.h"

Timer::Timer() {

    mCurrentTime = 0;
    mLastTime = 0;
}

Timer::~Timer() {}


void Timer::reset() {

    getCurrent();
}

Uint64 Timer::getCurrent() {
    mLastTime = mCurrentTime;
    mCurrentTime = SDL_GetPerformanceCounter();
    return mCurrentTime;
}


double Timer::deltaTime() {

    return ((mCurrentTime - mLastTime) * 1000/(double)SDL_GetPerformanceFrequency());
}