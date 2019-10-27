#ifndef SDLDISPLAY_H
#define SDLDISPLAY_H

#include <SDL2/SDL.h>
#include "display.h"
#include "events/event_controller.h"

class Application;

class SDLDisplay : public Display, public Publisher
{
public:
    SDLDisplay();
    ~SDLDisplay();

    void refresh();
    bool init(int w, int h);
    void uninit();
    void handleEvents();
    void clear();
    void sendEvent(std::shared_ptr<Event> ev) override;
    std::string name() override { return "SDLDisplay"; }

    SDL_Window *getWindow() const { return mpWindow; }
    SDL_Renderer *getRenderer() const { return mpRenderer; }

private:
    SDL_Window *mpWindow;
    SDL_Renderer *mpRenderer;
    int mWidth, mHeight;
    // Application *mApp;
};

#endif // !SDLDISPLAY_H
