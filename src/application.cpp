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


Application::~Application() {
}

void Application::uninit() {

    EventController::getInstance()->unrequestAllEvents(SP_APP);

    // Delete all our Singletons
    TextureManager::getInstance()->destroy();
    EventController::getInstance()->destroy();

    mDisplay->uninit();

    delete mDisplay;
    mDisplay = nullptr;

}

bool Application::init() {

    mDisplay = new SDLDisplay();

    if (!mDisplay->init(800,600))
        return false;

    SDL_RenderSetLogicalSize(mDisplay->getRenderer(), 320, 192);
    
    EventController::getInstance()->requestEvent(Event::EventType::WINDOW_CLOSE, SP_APP);


    // Testing ECS
    newPlayer.addComponent<TransformComponent>();
    newPlayer.addComponent<SpriteComponent>("assets/player.png", "player" );
    
    return true;
}

void Application::update(float dt) {

    manager.update(dt);
    
}

void Application::refresh() {

    // clear the screen
    mDisplay->clear();

    manager.draw();

    // refresh and display!
    mDisplay->refresh();
}

// TODO: Remove this!
float FPS = 60.f;
float FrameTime = 1000/FPS;
float dt =0.f;

void Application::run() {

    mbRunning = init(); // falls through on error

    unsigned int previous = SDL_GetTicks();
    unsigned int lag = 0;

   

    while (mbRunning) {

        mRenderTimer.reset();

        mDisplay->handleEvents();
        
        EventController::getInstance()->sendEvents();

        update(dt);
        refresh();

        dt = (float)mRenderTimer.deltaTime();
        
        if (dt < FrameTime) {
            SDL_Delay((int)(FrameTime - dt));
        }
        
        //mRenderTimer.reset();
    }

    uninit();

}

void Application::receiveEvent(std::shared_ptr<Event> ev) {

    if (ev->type() == Event::EventType::WINDOW_CLOSE) {
        quit();
    }
}