#include "Game.h"

SDL_Event Engine::GameEngine::event_;

Engine::GameEngine::GameEngine(SDLCallbacks * cb, std::string title, uint32_t width, uint32_t height, uint32_t xpos, uint32_t ypos, bool fullscreen):
    cb_(cb), title_(title), width_(width), height_(height), fullscreen_(fullscreen)
{
    int flags;

    flags = (fullscreen) ? (SDL_WINDOW_FULLSCREEN) : 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw std::runtime_error("SDL_Init() failed to initialize!!");
    }

    window_ = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);

    if (!window_)
    {
        throw std::runtime_error("SDL_CreateWindow() failed to create window!!");
    }

    renderer_ = SDL_CreateRenderer(window_, -1, 0);

    if (!renderer_)
    {
        SDL_DestroyWindow(window_);
        throw std::runtime_error("SDL_CreateRenderer() failed to create renderer!!");
    }

    SDL_SetRenderDrawColor(renderer_, 200, 200, 230, 255);

    cb_->onInit(renderer_); // This will let application load assets 
}

void Engine::GameEngine::renderMainLoop() noexcept
{
    const double FPS = 60;
    const double frameDelay = 1000.0 / FPS;
    double elapsedTime = 0.0;

    static auto timeStart_ = std::chrono::time_point_cast<milisec>(std::chrono::high_resolution_clock::now());


    while (handleEvent())
    {
        const auto newTimeStamp = std::chrono::time_point_cast<milisec>(std::chrono::high_resolution_clock::now());
        //Time from start of game loop
        const double deltaTime = std::chrono::duration<double>(newTimeStamp - timeStart_).count(); //time_point.count is long long hence doube cast


        SDL_RenderClear(renderer_);

        cb_->onUpdateFrame(renderer_, deltaTime);
        cb_->onRenderFrame(renderer_, deltaTime);

        SDL_RenderPresent(renderer_);

        //Time to render this frame
        timeStamp_ = std::chrono::time_point_cast<milisec>(std::chrono::high_resolution_clock::now()); //This is time_point
        elapsedTime = std::chrono::duration<double>(timeStamp_ - newTimeStamp).count();

        //To control rendering to 60 FPS
        if (frameDelay > elapsedTime)
        {
            SDL_Delay(static_cast<int>(frameDelay - elapsedTime));
        }
    }
}

bool Engine::GameEngine::handleEvent() noexcept
{
    SDL_PollEvent(&event_);

    switch (event_.type)
    {
    case SDL_QUIT:
        return false;

    case SDL_KEYDOWN:
    case SDL_KEYUP:

        cb_->onKey(renderer_, event_.key.keysym.sym, event_.type == SDL_KEYDOWN);
        break;
    case SDL_WINDOWEVENT:

        if (event_.window.type == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            width_ = event_.window.data1;
            height_ = event_.window.data2;

            cb_->onViewportSizeChanged(renderer_, width_, height_);
        }
        break;
    default:
        break;
    }

    return true;
}
