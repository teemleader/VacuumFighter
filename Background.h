#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include <string>

class Background {

private:
    inline static std::string animName = "backdrop";

public:
    static void Change(std::string& newanim);
    static void Draw();

};

#endif // _BACKGROUND_h
