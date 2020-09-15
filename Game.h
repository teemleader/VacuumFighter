#ifndef _GAME_H
#define _GAME_H

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

class Game {

private:
    const std::string gameName = "Vacuum Fighter";
    const std::string gameVersion = "v0.01";

public:
    Game();
    virtual ~Game();

    void GameLoop();
    void Update();
    void Draw();

};

#endif // _GAME_H
