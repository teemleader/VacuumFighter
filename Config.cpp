#include "Config.h"

void Config::Defaults() {
    Config::values.windowWidth = 1024;
    Config::values.windowHeight = 768;
    Config::values.fpsLimit = 60;

    Config::values.keyLeft = SDL_SCANCODE_LEFT;
    Config::values.keyRight = SDL_SCANCODE_RIGHT;
    Config::values.keyUp = SDL_SCANCODE_UP;
    Config::values.keyDown = SDL_SCANCODE_DOWN;
    Config::values.keyAccept = SDL_SCANCODE_RETURN;
    Config::values.keyBack = SDL_SCANCODE_ESCAPE;
}

void Config::Load() {
    // try open config file blabla
    // else
    Config::Defaults();
}
