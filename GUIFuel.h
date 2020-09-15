#ifndef _GUIFUEL_H
#define _GUIFUEL_H

#include <fstream>
#include <string>
#include <iostream>
#include "Rules.h"

class GUIFuel {

public:
    inline static unsigned int x = 20;
    inline static unsigned int y = 20;

    inline static int fuelMax = 0;
    inline static int fuel = 0;

    static void Init();
    static void Drain(unsigned int amount);
    static void Draw();

};

#endif // _GUIFUEL_H
