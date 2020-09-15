#ifndef _WINDOW_H
#define _WINDOW_H

#include <windows.h>
#undef CreateWindow
#undef DestroyWindow
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL_image.h>

// STATIC CLASS WINDOW
class Window {

private:
    inline static SDL_Window* handle = nullptr;
    inline static int sdlInited = -1;
    inline static bool exitInited = false;

public:
    static void CreateWindow(std::string titleBar, int width, int height);
    static bool Initialized();
    static SDL_Window* GetHandle();
    static void DestroyWindow();

    static bool Alive();
    static void HandleEvents();
    static void ShowMessage(std::string title, std::string message, bool error = false);
    static void ThrowError(std::string title, std::string message);
    static void SpawnConsole();

};

#endif // _WINDOW_H
