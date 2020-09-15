#include "Game.h"

#include "Config.h"
#include "Window.h"
#include "Renderer.h"
#include "Keyboard.h"
#include "TextureManager.h"

#include "View.h"
#include "World.h"
#include "GameObject.h"
#include "AnimationManager.h"
#include "MapManager.h"

#define DEBUGGING
//#include "Debug.h"


Game::Game() {
    Config::Load();
    Window::CreateWindow(this->gameName + " " + this->gameVersion, Config::values.windowWidth, Config::values.windowHeight);
    Renderer::CreateRenderer();
    Keyboard::Init();

    TextureManager::LoadTextureFiles();
    AnimationManager::LoadAnimationFiles();
    MapManager::LoadMaps();

    #ifdef DEBUGGING
    Window::SpawnConsole();
    #endif
}

Game::~Game() {
    Renderer::DestroyRenderer();
    Window::DestroyWindow();
}

void Game::GameLoop() {
    //World::Init();
    MapManager::StartMap("1");

    while (Window::Alive()) {
        Renderer::StartFrame();

        this->Update();
        this->Draw();

        Renderer::EndFrame();
    }
}

void Game::Update() {
    Window::HandleEvents();
    Keyboard::Update();
    World::Update();
}

void Game::Draw() {
    Renderer::Clear();

    World::Draw();

    Renderer::Present();
}
