#ifndef _VIEW_H
#define _VIEW_H

#include "GameObject.h"

class View {

private:
    inline static double xLeft = 0;
    inline static double yTop = 0;

    inline static unsigned int width = 0;
    inline static unsigned int height = 0;

    inline static double scale = 1.d;

public:
    inline static double x = 0;
    inline static double y = 0;

    static void SetScale(double newScale);
    static void AddScale(double amount);
    static void UpdateView();
    static void Move(double newX, double newY);
    static void MoveCenter(double newX, double newY);

    static bool ObjectVisible(GameObject* obj);
    static SDL_Rect ObjectTransformTexture(GameObject* obj);


};

#endif // _VIEW_H
