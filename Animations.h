#ifndef _ANIMATIONS_H
#define _ANIMATIONS_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "SingleAnimation.h"

class Animations {

public:
    std::string current = "";
    std::map<std::string, SingleAnimation> animations;

public:
    Animations();
    ~Animations();

    SingleAnimation* Add(const std::string& name);

    std::string GetCurrentAnimationName();
    SingleAnimation* GetCurrentAnimation();
    SDL_Texture* GetCurrentFrame();
    SDL_Rect GetSourceRect();
    bool HasAnimation(const std::string& name);

    void Change(const std::string& name);
    bool Finished();

    void Update();

};

#endif // _ANIMATIONS_H
