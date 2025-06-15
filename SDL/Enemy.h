#pragma once
#include "GameObject.h"
#include "Utils.h"

class Enemy : public GameObject {
private:
    Vector2 velocity;
    float changeDirTimer = 1.0f;

public:
    Enemy(SDL_Renderer* renderer, Vector2 pos);
    void Update(float dt) override;
    bool CheckCollision(const Vector2& point) const;
};
