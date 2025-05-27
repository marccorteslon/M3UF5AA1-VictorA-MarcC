#pragma once
#include "Scene.h"
#include "Player.h"
#include "Asteroid.h"  // << a�ade esta l�nea
#include <vector>

class GameplayScene : public Scene {
public:
	GameplayScene()
		: Scene() {
	}

	void Start(SDL_Renderer* rend) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;
	void Exit()override;

private:
	std::vector<GameObject*> asteroids;  // Para gestionar asteroides si quieres separados
};
