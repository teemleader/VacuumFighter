#ifndef _MAPMANAGER_H
#define _MAPMANAGER_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include "GameObject.h"
#include "SimpleConfig.h"

class MapManager {

private:
    inline static std::map<std::string, SimpleConfigFile> maps;
    inline static std::string currentMap = "1";

public:
    static void LoadMaps();
    static void LoadMapFile(const std::string& name, const std::string& path);

    static void StartMap(const std::string& name);
    static void RestartMap();

};

#endif // _MAPMANAGER_H
