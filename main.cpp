#include <windows.h>
#include <iostream>
#include <SDL2/SDL.h>

#include "Game.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpCmdLine, INT nCmdShow) {
    Game* game = new Game();

    game->GameLoop();

    delete game;

    return 0;
}
