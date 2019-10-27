#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

class InputManager
{

private:
    InputManager();

    static InputManager *spInstance;

public:
    static InputManager *getInstance();
    static void destroy();

    void handleInput();
};
#endif // !INPUT_MANAGER_H