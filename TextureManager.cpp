#include "TextureManager.h"
#include "Renderer.h"
#include "Window.h"
#include "FileManager.h"

SDL_Texture* TextureManager::TextureFromFile(const std::string& filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface) return NULL;

    SDL_Texture* result = SDL_CreateTextureFromSurface(Renderer::GetHandle(), surface);
    TextureManager::lastWidth = surface->w;
    TextureManager::lastHeight = surface->h;

    SDL_FreeSurface(surface);

    return result;
}

void TextureManager::LoadTextureFiles() {
    std::vector<std::string> files = FileManager::FilesInDirectory("assets\\img\\", "png");
    for (auto i : files) {
        // maybe check for i+".info" and then blah blah
        TextureManager::texturefiles[i] = TextureManager::TextureFromFile("assets\\img\\" + i + ".png");

        SDL_Rect srcrect = {0, 0, TextureManager::lastWidth, TextureManager::lastHeight};
        TextureManager::texturesources[i] = srcrect;
    }
}

void TextureManager::DestroyTextureFiles() {
    for (auto const& [key, value] : TextureManager::texturefiles) {
        SDL_DestroyTexture(value);
    }
    TextureManager::texturefiles.clear();
}


SDL_Texture* TextureManager::Get(const std::string& name) {
    auto it = TextureManager::texturefiles.find(name);
    if (it != TextureManager::texturefiles.end()) {
        return it->second;
    }
    return nullptr;
}

SDL_Rect TextureManager::GetSourceRect(const std::string& name) {
    auto it = TextureManager::texturesources.find(name);
    if (it != TextureManager::texturesources.end()) {
        return it->second;
    }
    return {0, 0, 0, 0};
}
