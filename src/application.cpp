#include "application.h"
#include "sdldisplay.h"
#include "events/event_controller.h"
#include "texture_manager.h"
#include "ECS/ECS.h"
#include "ECS/components.h"


extern std::shared_ptr<Application> SP_APP;
Manager manager;
auto& newPlayer(manager.addEntity());

Application::Application()  {}


Application::~Application() {}

void Application::uninit() {}

bool Application::init() {

    mDisplay = new SDLDisplay();

    if (!mDisplay->init(800,600))
        return false;

    EventController::getInstance()->requestEvent(Event::EventType::WINDOW_CLOSE, SP_APP);


    // Testing ECS
    newPlayer.addComponent<TransformComponent>();
    newPlayer.addComponent<SpriteComponent>("assets/player.png", "player" );
    
    return true;
}

void Application::update() {

    manager.update();
    
}

void Application::refresh() {

    // clear the screen
    mDisplay->clear();

    manager.draw();

    // refresh and display!
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