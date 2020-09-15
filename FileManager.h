#ifndef _FILEMANAGER_H
#define _FILEMANAGER_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <dirent.h>

// #include <filesystem> does not compile under MinGW for Windows so...

class FileManager {

public:
    static std::string getFileExt(const std::string& filename);
    static std::string getFileName(const std::string& filename);

    static std::vector<std::string> FilesInDirectory(const std::string& directory, const std::string& extension);

};

#endif // _FILEMANAGER_H
