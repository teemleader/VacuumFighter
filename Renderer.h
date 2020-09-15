#ifndef _RENDERER_H
#define _RENDERER_H

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

struct RenderTimers {
    unsigned int frameDelay;
    Uint32 frameStart;
    Uint32 frameEnd;
};

// STATIC CLASS RENDERER
class Renderer {

private:
    inline static SDL_Renderer* handle = nullptr;
    inline static RenderTimers timers = {0};

public:
    static void CreateRenderer();
    static bool Initialized();
    static SDL_Renderer* GetHandle();
    static void DestroyRenderer();

    static void StartFrame();
    static void EndFrame();

    static void Clear();
    static void Present();

    static void DrawRectangle(SDL_Rect& rect, int r, int g, int b, int a);
    static void DrawFillRectangle(SDL_Rect& rect, int r, int g, int b, int a);
    static void DrawTexture(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest, const double angle);

};

#endif // _RENDERER_H
