#ifndef APPLICATION_H
#define APPLICATION_H

class SDLDisplay;

#include "events/event_controller.h"

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

    //static std::shared_ptr<Application> spInstance;
    
    

    void update();

    bool init();

    void uninit();

    void refresh();

    bool mbRunning { false };

    SDLDisplay* mDisplay;
};

#endif // APPLICATION_H