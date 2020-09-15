#include "GameObject.h"
#include "View.h"
#include "Renderer.h"
#include "AnimationManager.h"
#include "GUIRadar.h"
#include "TextureManager.h"
#include "PlayerMovement.h"
#include "Physics.h"
#include "math.h"

GameObject::GameObject() {

}

GameObject::GameObject(const std::string& animationsName) {
    AnimationManager::AssignAnimations(this, animationsName);
    this->animationsName = animationsName;
    this->animations.Change("default");
    this->SizeFromAnimation();
    this->velX = 0;
    this->velY = 0;
    this->accX = 0;
    this->accY = 0;
}

GameObject::~GameObject() {

}

void GameObject::SizeFromAnimation() {
    SDL_Rect srcrect = this->animations.GetSourceRect();
    this->width = srcrect.w;
    this->height = srcrect.h;
    this->radius = this->width / 2;
}

void GameObject::AddAngle(double amount) {
    this->angle += amount;
    if (this->angle > 360.d) this->angle -= 360.d;
    if (this->angle < 0.d) this->angle += 360.d;
}

void GameObject::Rotate(double amount) {
    this->rotateRate = amount;
}

void GameObject::Update() {
    if (this->destroyed) return;

    if (!this->ready) this->ready = true;

    this->animations.Update();

    if (!this->active && this->mountedTo != nullptr) {
        this->x = this->mountedTo->x + cos(Physics::Radian(this->mountedTo->angle) + this->mountAngle) * (this->mountedTo->radius + this->radius + 0.01d);
        this->y = this->mountedTo->y + sin(Physics::Radian(this->mountedTo->angle) + this->mountAngle) * (this->mountedTo->radius + this->radius + 0.01d);
        this->angle = this->mountedTo->angle + Physics::Degrees(this->mountAngle);
        this->animations.Change("stationary");
        this->velX = 0.d;
        this->velY = 0.d;
        return;
    }

    this->velX += this->accX;
    this->velY += this->accY;

    this->x += this->velX;
    this->y += this->velY;

    if (this->waitForDestroyedAnimation) {
        this->Stop();
        if (this->animations.Finished()) this->destroyed = true;
        return;
    }

    if (this->health < 1) this->Destroy();

    this->angle += this->rotateRate;
}

void GameObject::Stop() {
    this->velX *= 0.8d;
    this->velY *= 0.8d;
    this->accX = 0;
    this->accY = 0;
}

void GameObject::Draw() {
    if (this->destroyed) return;
    if (!View::ObjectVisible(this)) return;

    SDL_Texture* currentFrame = this->animations.GetCurrentFrame();
    SDL_Rect src = this->animations.GetSourceRect();
    SDL_Rect dest = View::ObjectTransformTexture(this);

    if (currentFrame != nullptr) Renderer::DrawTexture(currentFrame, &src, &dest, this->angle);
}

void GameObject::DrawOnRadar() {
    if (this->destroyed) return;
    if (!GUIRadar::ObjectVisible(this)) return;

    SDL_Texture* currentFrame = this->animations.GetCurrentFrame();
    SDL_Rect src = this->animations.GetSourceRect();
    SDL_Rect dest = GUIRadar::ObjectTransformTexture(this);

    // draw player indicator on the radar
    if (this == PlayerMovement::GetPlayer()) {
        currentFrame = TextureManager::Get("playerradar");

        double xCenter = dest.x + dest.w / 2;
        double yCenter = dest.y + dest.h / 2;

        src = TextureManager::GetSourceRect("playerradar");
        dest.x = xCenter - ((double)src.w / 2.d);
        dest.y = yCenter - ((double)src.h / 2.d);
        dest.w = src.w;
        dest.h = src.h;
    }

    if (currentFrame != nullptr) Renderer::DrawTexture(currentFrame, &src, &dest, this->angle);
}

void GameObject::Destroy() {
    if (this->animations.HasAnimation("destroyed")) {
        this->waitForDestroyedAnimation = true;
        this->animations.Change("destroyed");
    } else {
        this->destroyed = true;
    }
}

bool GameObject::Destroyed() {
    return (this->destroyed || this->waitForDestroyedAnimation);
}
