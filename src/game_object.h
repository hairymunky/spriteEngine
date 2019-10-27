#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

//////////////////////////////////////////////////////////////////////
// GameObject
// A base class for all game objects. Allows game objects to both
// update and render themselves.
//////////////////////////////////////////////////////////////////////
class GameObject {
    public:

    GameObject() {}
    virtual ~GameObject() {}

    // Physics and Logic
    virtual void update() {}

    // Drawing
    virtual void render() {}
};

#endif //!GAME_OBJECT_H