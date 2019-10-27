#include "application.h"

#include <SDL2/SDL.h>

InputManager* InputManager::spInstance = nullptr;

static InputManager* InputManager::getInstance() {
    if(spInstance == nullptr)
        spInstance = new InputManager();

    return spInstance;
}


static void InputManager::destroy() {
    delete spInstance;
}

void InputManager::handleInput() {

    SDL_Event evt;

    while (SDL_PollEvent(&evt)) {

        if (evt.type == SDL_QUIT) {
            Application::getInstance()->quit();
        }
    }
}