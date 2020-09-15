#ifndef _SINGLEANIMATION_H
#define _SINGLEANIMATION_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>

class SingleAnimation {

private:
    std::vector<SDL_Texture*> frames;
    unsigned int framesCount;
    unsigned int currentFrame;

    unsigned int delay = 5;
    unsigned int counter = 0;
    bool finished = false;
    bool loop = false;

    SDL_Rect srcrect = {0};

public:
    SingleAnimation();
    virtual ~SingleAnimation();

    void AddFrame(SDL_Texture* frame);
    void AddFrame(const std::string& textureName);
    void NextFrame();
    void SetLoop(bool value);
    void SetDelay(unsigned int newDelay);
    bool Finished();

    void Reset();
    void Update();
    SDL_Texture* GetCurrentFrame();
    SDL_Rect GetSourceRect();

};

#endif // _ANIMATION_H
