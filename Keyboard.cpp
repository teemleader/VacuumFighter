#include "Keyboard.h"
#include "Config.h"

void Keyboard::Init() {
    Keyboard::SDL_StatesPTR = (Uint8*)SDL_GetKeyboardState(NULL);
    /*for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        Keyboard::keyStates[i] = {false, false, false};
    }*/
}

void Keyboard::Update() {
    bool wasDownBefore;
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        wasDownBefore = Keyboard::keyStates[i].down;
        Keyboard::keyStates[i].down = Keyboard::SDL_StatesPTR[i];

        Keyboard::keyStates[i].pressed = (Keyboard::keyStates[i].down && !wasDownBefore);
        Keyboard::keyStates[i].released = (!Keyboard::keyStates[i].down && wasDownBefore);
    }
}

bool Keyboard::Down(Uint8 key) {
    return Keyboard::keyStates[key].down;
}

bool Keyboard::Up(Uint8 key) {
    return !Keyboard::keyStates[key].down;
}

bool Keyboard::Pressed(Uint8 key) {
    return Keyboard::keyStates[key].pressed;
}

bool Keyboard::Released(Uint8 key) {
    return Keyboard::keyStates[key].released;
}

int Keyboard::Horizontal() {
    return Keyboard::Down(Config::values.keyLeft) ? -1 : Keyboard::Down(Config::values.keyRight) ? 1 : 0;
}

int Keyboard::Vertical() {
    return Keyboard::Down(Config::values.keyUp) ? -1 : Keyboard::Down(Config::values.keyDown) ? 1 : 0;
}

int Keyboard::HorizontalPressed() {
    return Keyboard::Pressed(Config::values.keyLeft) ? -1 : Keyboard::Pressed(Config::values.keyRight) ? 1 : 0;
}

int Keyboard::VerticalPressed() {
    return Keyboard::Pressed(Config::values.keyUp) ? -1 : Keyboard::Pressed(Config::values.keyDown) ? 1 : 0;
}

bool Keyboard::Accept() {
    return Keyboard::Pressed(Config::values.keyAccept);
}

bool Keyboard::Back() {
    return Keyboard::Pressed(Config::values.keyBack);
}
