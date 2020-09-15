#include "Animations.h"

Animations::Animations() {

}

Animations::~Animations() {
    this->animations.clear();
}

SingleAnimation* Animations::Add(const std::string& name) {
    this->animations[name] = SingleAnimation();
    if (this->current.length() == 0) this->current = name;

    return &this->animations[name];
}

std::string Animations::GetCurrentAnimationName() {
    return this->current;
}

SingleAnimation* Animations::GetCurrentAnimation() {
    if (this->current.length() == 0) return nullptr;

    return &this->animations[this->current];
}

SDL_Texture* Animations::GetCurrentFrame() {
    if (this->current.length() == 0) return nullptr;

    return this->animations[this->current].GetCurrentFrame();
}

SDL_Rect Animations::GetSourceRect() {
    if (this->current.length() == 0) return {0};

    return this->animations[this->current].GetSourceRect();
}

bool Animations::HasAnimation(const std::string& name) {
    auto found = this->animations.find(name);
    return found != this->animations.end();
}

void Animations::Change(const std::string& name) {
    auto found = this->animations.find(name);
    if (found == this->animations.end()) return;

    if (this->current == name) return;

    this->current = name;
    this->animations[name].Reset();
}

bool Animations::Finished() {
    if (this->current.length() == 0) return true;

    return this->animations[this->current].Finished();
}

void Animations::Update() {
    if (this->current.length() == 0) return;

    //if (animationsName == "ship") {
        //std::cout << this->animations["flying"]->framesCount << std::endl;
        //std::cout << this->animations.animations["flying"]->framesCount << std::endl;
       // std::cout << this->animations.animations["destroyed"]->framesCount << std::endl;
    //}

    this->animations[this->current].Update();
}


