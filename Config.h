#ifndef _CONFIG_H
#define _CONFIG_H

#include <windows.h>
#undef CreateWindow
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL_image.h>

struct ConfigValues {
    unsigned int windowWidth;
    unsigned int windowHeight;
    unsigned int fpsLimit;
    unsigned int keyLeft;
    unsigned int keyRight;
    unsigned int keyUp;
    unsigned int keyDown;
    unsigned int keyAccept;
    unsigned int keyBack;
};

// STATIC CLASS CONFIG
class Config {

public:
    inline static ConfigValues values = {0};
    static void Defaults();
    static void Load();

};

#endif // _CONFIG_H
