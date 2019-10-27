#include "application.h"
#include "sdldisplay.h"
#include "events/event_controller.h"

extern std::shared_ptr<Application> SP_APP;

Application::Application() {}


Application::~Application() {}

void Application::uninit() {}

bool Application::init() {

    mDisplay = new SDLDisplay();

    if (!mDisplay->init(800,600))
        return false;

    EventController::getInstance()->requestEvent(Event::EventType::WINDOW_CLOSE, SP_APP);

    return true;
}

void Application::update() {

}

void Application::refresh() {

    mDisplay->clear();

    mDisplay->refresh();
}

// TODO: Remove this!
float FPS = 1.f/60.f;

void Application::run() {

    mbRunning = init(); // falls through on error

    unsigned int previous = SDL_GetTicks();
    unsigned int lag = 0;

    while (mbRunning) {

        unsigned int current = SDL_GetTicks();
        unsigned int elapsed = current - previous;
        previous = current;
        lag += elapsed;

        mDisplay->handleEvents();
        
        EventController::getInstance()->sendEvents();

        while (lag >= FPS) {
            update();
            lag -= FPS;
        }

        refresh();

    }

    uninit();

}

void Application::receiveEvent(std::shared_ptr<Event> ev) {

    if (ev->type() == Event::EventType::WINDOW_CLOSE) {
        quit();
    }
}