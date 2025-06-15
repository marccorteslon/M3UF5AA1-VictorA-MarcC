#include "GameEngine.h"
#include "GameObject.h"
#include "InputManager.h"
#include <SDL_ttf.h>

GameEngine::GameEngine(int windowWidth, int windowHeight) {
    InitSDL();
    InitWindowAndRenderer(windowWidth, windowHeight);
}

void GameEngine::Update() {
    float dt = 0.0f;
    float lastTime = (float)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();

    const int FPS = 60;
    const float frameTime = 1.0f / FPS;

    std::map<std::string, Scene*> gameScene;
    gameScene["MainMenu"] = new MenuScene();
    gameScene["Gameplay"] = new GameplayScene();
    gameScene["Highscores"] = new HighscoreScene();

    Scene* currentScene = gameScene["MainMenu"];
    currentScene->Start(renderer);
    SDL_RaiseWindow(window);

    while (!IM.GetQuit()) {
        IM.Listen();

        float currentTime = (float)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
        dt += currentTime - lastTime;

        if (dt >= frameTime) {
            currentScene->Update(dt);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            currentScene->Render(renderer);
            SDL_RenderPresent(renderer);

            if (currentScene->IsFinished()) {
                currentScene->Exit();
                currentScene = gameScene[currentScene->GetTargetScene()];
                currentScene->Start(renderer);
            }

            dt -= frameTime;
        }

        lastTime = currentTime;
    }
}

void GameEngine::Finish() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void GameEngine::InitSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "[ ERROR :) ] " << SDL_GetError() << std::endl;
    }
    if (TTF_Init() < 0) {
        std::cout << "[ ERROR :) ] " << TTF_GetError() << std::endl;
    }
}

void GameEngine::InitWindowAndRenderer(int windowWidth, int windowHeight) {
    window = SDL_CreateWindow(
        "Hecho por: Marc Cortes y Victor Arcas",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cout << "[ ERROR :) ]  " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "[ ERROR :) ] " << SDL_GetError() << std::endl;
    }
}
