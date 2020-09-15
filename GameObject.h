#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "Animations.h"

class GameObject {

private:
    bool waitForDestroyedAnimation = false;
    std::string animationsName;

    double rotateRate = 0.d;

public:
    bool destroyed = false;
    unsigned int health = 1000;

    double x, y = 0.d;
    double velX, velY = 0.d;
    double accX, accY = 0.d;

    double angle = 0.d;
    double radius = 0.d;

    double width = 0.d;
    double height = 0.d;

    double mass = 0.d;

    Animations animations;

    GameObject* mountedTo;
    double mountAngle = 0.d;
    bool active = true;

    bool colliding = false;

    bool ready = false;

public:
    GameObject();
    GameObject(const std::string& animationsName);
    virtual ~GameObject();

    void SizeFromAnimation();

    void Rotate(double amount);
    void AddAngle(double amount);

    void Stop();

    void Update();
    void Draw();
    void DrawOnRadar();

    void Destroy();
    bool Destroyed();

};

#endif // _GAMEOBJECT_H
