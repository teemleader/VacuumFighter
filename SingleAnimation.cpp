#include "SingleAnimation.h"
#include "TextureManager.h"

SingleAnimation::SingleAnimation() {
    this->framesCount = 0;
    this->currentFrame = 0;
}

SingleAnimation::~SingleAnimation() {

}

void SingleAnimation::AddFrame(SDL_Texture* frame) {
    this->frames.push_back(frame);
    this->framesCount++;
}

void SingleAnimation::AddFrame(const std::string& textureName) {
    SDL_Texture* frame = TextureManager::Get(textureName);
    if (frame == nullptr) return;

    this->AddFrame(frame);
    this->srcrect = TextureManager::GetSourceRect(textureName);
}

void SingleAnimation::NextFrame() {
    // back to the begining if there is no next frame
    if (this->currentFrame + 1 >= this->framesCount) {
        if (this->loop) {
            this->currentFrame = 0;
        } else {
            this->finished = true;
        }
    } else {
        this->currentFrame++;
    }
}

void SingleAnimation::SetDelay(unsigned int newDelay) {
    this->delay = newDelay;
}

void SingleAnimation::SetLoop(bool value) {
    this->loop = value;
}

bool SingleAnimation::Finished() {
    return this->finished;
}

void SingleAnimation::Reset() {
    this->counter = 0;
    this->currentFrame = 0;
    this->finished = false;
}

void SingleAnimation::Update() {
    this->counter++;
    if (this->counter >= this->delay) {
        this->counter = 0;
        this->NextFrame();
    }
}

SDL_Texture* SingleAnimation::GetCurrentFrame() {
    if (this->framesCount < 1) return nullptr;
    try {
        return this->frames[this->currentFrame];
    } catch (const std::out_of_range& oor) {
        return nullptr;
    }
}

SDL_Rect SingleAnimation::GetSourceRect() {
    return this->srcrect;
}
