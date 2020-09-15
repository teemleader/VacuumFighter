#include "FileManager.h"
#include "Window.h"

std::string FileManager::getFileExt(const std::string& filename) {
   size_t i = filename.rfind('.', filename.length());
   if (i != std::string::npos) {
      return(filename.substr(i+1, filename.length() - i));
   }

   return "";
}

std::string FileManager::getFileName(const std::string& filename) {
   size_t i = filename.rfind('.', filename.length());
   if (i != std::string::npos) {
      return(filename.substr(0, i));
   }

   return "";
}

std::vector<std::string> FileManager::FilesInDirectory(const std::string& directory, const std::string& extension) {
    std::vector<std::string> result;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (directory.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string filepath = ent->d_name;
            if (filepath == "." || filepath == "..") continue;

            std::string ext = FileManager::getFileExt(filepath);
            std::string name = FileManager::getFileName(filepath);
            if (ext == extension) result.push_back(name);
        }
        closedir (dir);
    } else {
        Window::ThrowError("FileSystem Error", "Cannot open directory: \""+directory+"\"");
    }
    return result;
}
