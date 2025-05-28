#include "GameEngine.h"
#include "GameObject.h"

GameEngine::GameEngine(int windowWidth, int windowHeight) {
	InitSDL();
	InitWindowAndRenderer(windowWidth, windowHeight);

}

void GameEngine::Update() {
    bool quitGame = false;

    // Map de escenas
    std::map<std::string, Scene*> gameScenes;
    gameScenes["MainMenu"] = new MenuScene();
    gameScenes["Gameplay"] = new GameplayScene();
    gameScenes["Highscores"] = new HighscoresScene();

    // Empezamos en gameplay (puedes cambiar a MainMenu si quieres)
    Scene* currentScene = gameScenes["Gameplay"];
    currentScene->Start(renderer);

    // Tiempo para deltaTime
    float lastTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
    float dt = 0.0f;

    // Frames por segundo objetivo
    const int FPS = 60;
    const float frameTime = 1.0f / (float)FPS;

    while (!quitGame) {
        // Tiempo actual
        float currentTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
        dt += currentTime - lastTime;
        lastTime = currentTime;

        // Procesar todos los eventos SDL
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quitGame = true;
            }
        }

        // Si ha pasado suficiente tiempo para un frame, actualizamos y renderizamos
        if (dt >= frameTime) {
            // Actualizamos la escena con delta time (en segundos)
            currentScene->Update(dt);

            // Limpiar pantalla con un color de fondo (naranja en este caso)
            SDL_SetRenderDrawColor(renderer, 255, 120, 0, 255);
            SDL_RenderClear(renderer);

            // Renderizamos la escena actual
            currentScene->Render(renderer);

            // Mostrar lo que hemos dibujado
            SDL_RenderPresent(renderer);

            // Gestionar cambio de escenas
            if (currentScene->IsFinished()) {
                currentScene->Exit();

                std::string nextSceneName = currentScene->GetTargetScene();
                if (gameScenes.find(nextSceneName) != gameScenes.end()) {
                    currentScene = gameScenes[nextSceneName];
                    currentScene->Start(renderer);
                }
                else {
                    // Si no hay escena siguiente, salir del juego
                    quitGame = true;
                }
            }

            // Restar el frameTime a dt para compensar el tiempo ya consumido
            dt -= frameTime;
        }
        else {
            // Si no ha pasado tiempo suficiente para el siguiente frame, dormir un poco
            SDL_Delay(1);
        }
    }

    // Liberar memoria de las escenas creadas
    for (auto& pair : gameScenes) {
        pair.second->Exit();
        delete pair.second;
    }
}



void GameEngine::Finish() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void GameEngine::InitSDL() {
	int result = SDL_Init(SDL_INIT_VIDEO);

	if (result < 0) {
		std::cout << "Error al inicialzar SDL:" << SDL_GetError();
	}
}
void GameEngine::InitWindowAndRenderer(int windowWidth, int windowHeight) {
	//WINDOWS
	window = SDL_CreateWindow("My Fist Game Engine",		//NAME
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,		//POSITION
		windowWidth, windowHeight,							//SIZE
		SDL_WINDOW_SHOWN);									//SHOW BY DEFAULT
				
	if (window == nullptr) {
		std::cout << "Error al inicialzar window:" << SDL_GetError();
	}

	//RENDERER
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Error al inicialzar window:" << SDL_GetError();
	}

}