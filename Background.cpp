#include "Background.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "World.h"
#include "View.h"
#include "GameObject.h"

void Background::Draw() {
    //SDL_Texture* backdrop = TextureManager::Get("backdrop");
    GameObject* backobj = new GameObject(Background::animName);
    for (unsigned int x = 0; x < World::width / 800 + 1; x++) {
        for (unsigned int y = 0; y < World::height / 800 + 1; y++) {
            backobj->x = x*800;
            backobj->y = y*800;
            backobj->Draw();
        }
    }
    delete backobj;
}

void Background::Change(std::string& newanim) {
    Background::animName = newanim;
}
