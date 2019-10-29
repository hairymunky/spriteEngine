#ifndef APPLICATION_H
#define APPLICATION_H

class SDLDisplay;

#include "events/event_controller.h"
#include "ECS/ECS.h"
#include "timer.h"

class Application : public Handler
{

public:
    
    // static Application* getInstance(); 
    // static void destroy();
    Application();

    virtual ~Application();

    void run();

    void quit() { mbRunning = false; }

    SDLDisplay* getDisplay() const { return mDisplay; }

    std::string name() override { return "Application"; }
    
    virtual void receiveEvent(std::shared_ptr<Event> ev) override;

private:

    void update();

    bool init();

    void uninit();

    void refresh();

    bool mbRunning { false };

    SDLDisplay* mDisplay;
    Manager     mManager;
    Timer       mRenderTimer;
};

#endif // APPLICATION_H