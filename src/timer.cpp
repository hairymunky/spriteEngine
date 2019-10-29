#include "timer.h"

Timer::Timer() {

    mFrameStart = 0;
    mDeltaTime = 0.f;
}

Timer::~Timer() {}


void Timer::reset() {

    mFrameStart = SDL_GetPerformanceCounter();
}

double Timer::deltaTime() {

    Uint64 end = SDL_GetPerformanceCounter();

    mDeltaTime = ((end - mFrameStart)*1000/(double)SDL_GetPerformanceFrequency());
    return mDeltaTime;
}