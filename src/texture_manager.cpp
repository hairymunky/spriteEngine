#include "texture_manager.h"
#include "application.h"
#include <SDL2/SDL_image.h>



TextureManager* TextureManager::spInstance = nullptr;

TextureManager *TextureManager::getInstance() {

    if (spInstance == nullptr) {
        spInstance = new TextureManager();
    }

    return spInstance;
}


TextureManager::TextureManager() {

    // init SDL Image. Called once you get the singleton
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL failed to init the Image library: %s\n", IMG_GetError());
    }

}


TextureManager::~TextureManager() {

    // delete the textures in the map
    for( auto it = mTextureMap.begin(); it!= mTextureMap.end(); ++it) {
        //delete *it->second;
        SDL_DestroyTexture(it->second);
        mTextureMap.erase(it);
    }
}

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer * pRenderer) {

    SDL_Surface* pTempSurface = IMG_Load(filename.c_str());

    if (pTempSurface == 0) {
        return false; // something went wrong ):
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    if (pTexture != 0) {
        mTextureMap[id] = pTexture;
        return true;
    }

    return false;
}


void TextureManager::draw(std::string id, int x, int y, int w, int h, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {

    SDL_Rect src;
    SDL_Rect dst;

    src.x = src.y = 0;
    src.w = dst.w = w;
    src.h = dst.h = h;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopyEx(pRenderer, mTextureMap[id], &src, &dst, 0, 0, flip);
}


void TextureManager::drawFrame(std::string id, int x, int y, int w, int h, int currRow, int currFrame, SDL_Renderer * pRenderer, SDL_RendererFlip flip) {

    SDL_Rect src;
    SDL_Rect dst;
    src.x = w * currFrame;
    src.y = h * (currRow - 1);
    src.w = dst.w = w;
    src.h = dst.h = h;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopyEx(pRenderer, mTextureMap[id], &src, &dst, 0, 0, flip);    
}