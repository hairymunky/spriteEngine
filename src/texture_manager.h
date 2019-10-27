#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <string>
#include <map>

class TextureManager {

    private:

        TextureManager();
        ~TextureManager();
        static TextureManager *spInstance;
        std::map<std::string, SDL_Texture*> mTextureMap;

    public:

        static TextureManager* getInstance();
        static void destroy() { delete spInstance; }

        bool load(std::string fileName, std::string id, SDL_Renderer * pRenderer);

        void draw(std::string id, int x, int y, int w, int h, SDL_Renderer * pRenderer, SDL_RendererFlip flip= SDL_FLIP_NONE);

        void drawFrame(std::string id, int x, int y, int w, int h, int currRow, int currFrame, SDL_Renderer * pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
};


#endif