#include "application.h"
#include "sdldisplay.h"
#include "events/event_controller.h"
#include "texture_manager.h"
#include "ECS/ECS.h"
#include "ECS/components.h"


Application* Application::spInstance = nullptr;

Application* Application::getInstance() {

    if (spInstance == nullptr)
        spInstance = new Application();

    return spInstance;
}

void Application::destroy() {

    delete spInstance;
    spInstance = nullptr;
}

Manager manager;
auto& newPlayer(manager.addEntity());

Application::Application()  {}


Application::~Application() {}

void Application::uninit() {

    EventController::getInstance()->destroy();
    
}

bool Application::init() {

    mDisplay = new SDLDisplay();

    if (!mDisplay->init(800,600))
        return false;

    EventController::getInstance()->requestEvent(Event::EventType::WINDOW_CLOSE, this);


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

int Application::run() {

    if (!init()) {
        return EXIT_FAILURE;
    }

    mbRunning = true; 
  

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

    return EXIT_SUCCESS;

}

void Application::receiveEvent(Event* ev) {

    if (ev->type() == Event::EventType::WINDOW_CLOSE) {
        quit();
    }
}