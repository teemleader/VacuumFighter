#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_image.h>

class Keyboard {

private:
    inline static struct keyInfo {
        bool down;
        bool pressed;
        bool released;
    } keyStates[SDL_NUM_SCANCODES] = {0};

    inline static Uint8* SDL_StatesPTR = nullptr;

public:
    static void Init();
    static void Update();

    static bool Down(Uint8 key);
    static bool Up(Uint8 key);
    static bool Pressed(Uint8 key);
    static bool Released(Uint8 key);

    static int Horizontal();
    static int Vertical();
    static int HorizontalPressed();
    static int VerticalPressed();
    static bool Accept();
    static bool Back();

};

#endif
