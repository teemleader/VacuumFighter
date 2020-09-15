#include "Renderer.h"
#include "Window.h"
#include "Config.h"

void Renderer::CreateRenderer() {
    Renderer::handle = SDL_CreateRenderer(Window::GetHandle(), -1, 0);
    if (Renderer::handle == nullptr) Window::ThrowError("Cannot init renderer", SDL_GetError());

    Renderer::timers.frameDelay = 1000 / Config::values.fpsLimit;
}

bool Renderer::Initialized() {
    return Renderer::handle != nullptr;
}

SDL_Renderer* Renderer::GetHandle() {
    return Renderer::handle;
}

void Renderer::DestroyRenderer() {
    if (Renderer::handle != nullptr) SDL_DestroyRenderer(Renderer::handle);
}

void Renderer::StartFrame() {
    Renderer::timers.frameStart = SDL_GetTicks();
}

void Renderer::EndFrame() {
    Renderer::timers.frameEnd = SDL_GetTicks();

    int frameTime = Renderer::timers.frameEnd - Renderer::timers.frameStart;
    int remainingDelay = Renderer::timers.frameDelay - frameTime;

    if (remainingDelay > 0) {
        SDL_Delay(remainingDelay);
    }
}

void Renderer::Clear() {
    SDL_RenderClear(Renderer::handle);
}

void Renderer::Present() {
    SDL_RenderPresent(Renderer::handle);
}

void Renderer::DrawRectangle(SDL_Rect& rect, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(Renderer::handle, r, g, b, a);
    SDL_RenderDrawRect(Renderer::handle, &rect);
    SDL_SetRenderDrawColor(Renderer::handle, 0, 0, 0, 255);
}

void Renderer::DrawFillRectangle(SDL_Rect& rect, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(Renderer::handle, r, g, b, a);
    SDL_RenderFillRect(Renderer::handle, &rect);
    SDL_SetRenderDrawColor(Renderer::handle, 0, 0, 0, 255);
}

void Renderer::DrawTexture(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest, const double angle) {
    SDL_RenderCopyEx(Renderer::handle, texture, src, dest, angle, NULL, SDL_FLIP_NONE);
}
