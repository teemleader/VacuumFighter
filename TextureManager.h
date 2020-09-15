#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>

class TextureManager {

private:
    inline static std::map<std::string, SDL_Texture*> texturefiles;
    inline static std::map<std::string, SDL_Rect> texturesources;
    inline static int lastWidth = 0;
    inline static int lastHeight = 0;

public:
    static SDL_Texture* TextureFromFile(const std::string& filename);
    static void LoadTextureFiles();
    static void DestroyTextureFiles();
    static SDL_Texture* Get(const std::string& name);
    static SDL_Rect GetSourceRect(const std::string& name);

};

#endif // _TEXTUREMANAGER_H
