#ifndef SPRITE_H
#define SPRITE_H

#include "ECS/ECS.h"
#include "ECS/transform.h"
#include "texture_manager.h"
#include <SDL2/SDL.h>
#include <string>

extern std::shared_ptr<Application> SP_APP;

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    std::string textureID;
    SDL_Rect src, dst;

public:

    SpriteComponent() = default;
    SpriteComponent(std::string filename, std::string id) {

        if (!TextureManager::getInstance()->load(filename, id,
        SP_APP->getDisplay()->getRenderer())) {
            printf("Error loading texture: %s\n", filename.c_str());
        }

        textureID = id;
    }

    void init() override {

        transform = &entity->getComponent<TransformComponent>();

        // TODO: Remove hardcoded values!
        src.x = src.y = 0;
        src.w = src.h = 32;
        dst.w = dst.h = 32;

    }

    void update(float dt) override {

        dst.x = transform->x();
        dst.y = transform->y();
    }

    void draw() override {

        // TODO: Render the sprite
        TextureManager::getInstance()->draw(
            textureID, dst.x, dst.y,
            dst.w, dst.h,
            SP_APP->getDisplay()->getRenderer()
        );
    }

};
#endif