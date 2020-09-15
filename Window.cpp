#include "Window.h"
#include "Renderer.h"

void Window::CreateWindow(std::string titleBar, int width, int height) {
    Window::sdlInited = SDL_Init(SDL_INIT_EVERYTHING);
    if (Window::sdlInited < 0) Window::ThrowError("Cannot init SDL", SDL_GetError());

    Window::handle = SDL_CreateWindow(titleBar.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    if (Window::handle == nullptr) Window::ThrowError("Cannot init game window", SDL_GetError());
}

bool Window::Initialized() {
    return Window::sdlInited >= 0 && Window::handle != nullptr;
}

SDL_Window* Window::GetHandle() {
    return Window::handle;
}

void Window::DestroyWindow() {
    if (Window::handle != nullptr) SDL_DestroyWindow(Window::handle);
    if (Window::sdlInited) SDL_Quit();
}

bool Window::Alive() {
    return (!Window::exitInited && Window::Initialized() && Renderer::Initialized());
}

void Window::HandleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) Window::exitInited = true;
    }
}

void Window::ShowMessage(std::string title, std::string message, bool error) {
    const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" },
    };

    // to make title always visible message must have at least the length of the title
    auto expandMessage = [](std::string title, std::string message) {
        for (int i = title.length() - message.length(); i > 0; i--)
            message += " ";
        return message;
    };


    const SDL_MessageBoxData messageboxdata = {
        (error) ? SDL_MESSAGEBOX_ERROR : SDL_MESSAGEBOX_INFORMATION, /* .flags */
        Window::handle, /* .window */
        title.c_str(), /* .title */
        expandMessage(title, message).c_str(), /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        nullptr /* .colorScheme */
    };

    int buttonid;
    SDL_ShowMessageBox(&messageboxdata, &buttonid);
}

void Window::ThrowError(std::string title, std::string message) {
    Window::ShowMessage(title, message, true);
}

void Window::SpawnConsole() {
    AllocConsole();
    int hConHandle = _open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    FILE* fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );
}
