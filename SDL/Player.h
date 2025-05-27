#pragma once
#include "GameObject.h"
#include <cmath>

class Player : public GameObject {
public:
    Player(SDL_Renderer* renderer);

    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;

    float rotation; // grados

private:
    float speedLimit = 200.f;
    Vector2 velocity;
};
