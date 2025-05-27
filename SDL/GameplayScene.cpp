#include "GameplayScene.h"
#include <cstdlib>
#include <ctime>

void GameplayScene::Start(SDL_Renderer* rend) {
	Scene::Start(rend);

	// Crear jugador
	objects.push_back(new Player(rend));

	// Crear asteroides
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	for (int i = 0; i < 5; ++i) {
		Vector2 pos(static_cast<float>(rand() % 500), static_cast<float>(rand() % 500));
		Vector2 vel(static_cast<float>((rand() % 200) - 100), static_cast<float>((rand() % 200) - 100));

		Asteroid* asteroid = new Asteroid(rend, pos, vel);
		objects.push_back(asteroid);
	}
}

void GameplayScene::Update(float dt) {
	Scene::Update(dt);
}

void GameplayScene::Render(SDL_Renderer* rend) {
	Scene::Render(rend);
}

void GameplayScene::Exit() {
	for (auto obj : objects) {
		delete obj;
	}
	objects.clear();
}
