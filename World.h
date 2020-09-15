#ifndef _WORLD_H
#define _WORLD_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "GameObject.h"

class World {

public:
    inline static unsigned int width = 10000;
    inline static unsigned int height = 10000;

    inline static GameObject* player = nullptr;

    inline static int restartTimer = 0;

    static void Init();
    static void Destroy();

    static void Update();
    static void Draw();

    inline static std::vector<GameObject*> actors;
    static void AddActor(GameObject* obj);

};

#endif // _WORLD_H
