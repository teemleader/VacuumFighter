#ifndef _RADAR_H
#define _RADAR_H

#include "Renderer.h"
#include "GameObject.h"

class GUIRadar {

public:
    static void Init();
    static void Update();
    static void Draw();

    static SDL_Rect ObjectTransformTexture(GameObject* obj);
    static bool ObjectVisible(GameObject* obj);

    inline static SDL_Texture* renderTexture = nullptr;

    inline static int lineSize = 1;

    inline static int radarX = 800;
    inline static int radarY = 20;

    inline static int radarWidth = 204;
    inline static int radarHeight = 200;

    inline static double viewXLeft = 0;
    inline static double viewYTop = 0;

    inline static double viewWidth = 0;
    inline static double viewHeight = 0;

    inline static double scale = 0.2d;

};

#endif // _RADAR_H
