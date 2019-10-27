#include "application.h"
#include "sdldisplay.h"
#include "events/event_controller.h"
#include <cstdio>

void SDLDisplay::sendEvent(std::shared_ptr<Event> ev)  {

    EventController::getInstance()->addEventToQueue(ev);
}

SDLDisplay::SDLDisplay(/*Application* app*/) : mWidth(0), mHeight(0) {
    mpWindow = nullptr;
    mpRenderer = nullptr;
}

SDLDisplay::~SDLDisplay() {
    
    SDL_DestroyRenderer(mpRenderer);
    SDL_DestroyWindow(mpWindow);

    mpWindow = nullptr;
    mpRenderer = nullptr;

    SDL_Quit();
}

void SDLDisplay::refresh() {

    SDL_RenderPresent(mpRenderer);
}

void SDLDisplay::uninit() {

}

bool SDLDisplay::init(int _w, int _h) {

    if (SDL_Init(SDL_INIT_EVERYTHING)<0){
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    mpWindow = SDL_CreateWindow("SPRITE::ENGINE", 0, 0, _w, _h, SDL_WINDOW_SHOWN);

    if (mpWindow == nullptr) {
        printf("Error creating SDL Window: %s\n", SDL_GetError());
        return false;
    }

    mWidth = _w;
    mHeight = _h;

    mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED);

    if (mpRenderer == nullptr) {
        printf("Error creating SDL Renderer: %s\n", SDL_GetError());
        return false;
    }

    
    return true;
}


void SDLDisplay::clear() {
    
    SDL_SetRenderDrawColor(mpRenderer, 255,255,255,255); // Green for testing

    SDL_RenderClear(mpRenderer);
}


void SDLDisplay::handleEvents() {

    SDL_Event evt;

    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) {
            // Handle Quit event...
            std::shared_ptr<Event> ev = std::make_shared<WindowCloseEvent>();
            sendEvent(ev);
        }
    }
}