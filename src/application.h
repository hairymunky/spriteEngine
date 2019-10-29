#ifndef APPLICATION_H
#define APPLICATION_H

class SDLDisplay;

#include "events/event_controller.h"
#include "ECS/ECS.h"
#include "timer.h"

class Application : public Handler
{

public:
    
    static Application* getInstance(); 
    static void destroy();

    virtual ~Application();

    int run();

    void quit() { mbRunning = false; }

    SDLDisplay* getDisplay() const { return mDisplay; }

    std::string name() override { return "Application"; }
    
    virtual void receiveEvent(Event* ev) override;

private:

    Application();    

    void update(float dt);

    bool init();

    void uninit();

    void refresh();

    bool mbRunning { false };


    static Application* spInstance;
    SDLDisplay* mDisplay;
    Manager     mManager;
    Timer       mRenderTimer;
};

#endif // APPLICATION_H