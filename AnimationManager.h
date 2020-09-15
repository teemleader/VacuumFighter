#ifndef _ANIMATIONMANAGER_H
#define _ANIMATIONMANAGER_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include "GameObject.h"

/*
--- .ANIM FILE STRUCTURE: ---

:START      // start of single animation
default     // name of single animation (.anim file have to contain one animation named "default")
1           // play this animation in loop? ("1" or "true" means yes)
15          // animation delay time in frames
earth       // frame 1
redplanet   // frame 2 ... etc
:END        // end of single animation

*/

struct SingleAnimationInfo {
    std::string name;
    bool repeat;
    unsigned int delay;
    std::vector<std::string> frames;
};

struct AnimationsInfo {
    std::string name;
    std::map<std::string, SingleAnimationInfo> subAnimations;
};

class AnimationManager {

private:
    inline static std::map<std::string, AnimationsInfo> animations;
    static void LoadAnimationFile(const std::string& name, const std::string& path);

public:
    static void LoadAnimationFiles();
    static void AssignAnimations(GameObject* obj, std::string animsName);

};

#endif // _ANIMATIONMANAGER_H
