#pragma once
#include "GameObject.h"

class Asteroid : public GameObject {
public:
	Asteroid(SDL_Renderer* renderer, Vector2 spawnPos, Vector2 velocity);

	void Update(float dt) override;
	void Render(SDL_Renderer* renderer) override;

private:
	Vector2 velocity;
};
