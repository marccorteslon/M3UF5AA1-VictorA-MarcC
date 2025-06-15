#pragma once
#include "GameObject.h"
#include "Utils.h"
#include <SDL.h>

enum AsteroidSize { BIG, MEDIUM, SMALL };

class Asteroid : public GameObject {
public:
    Asteroid(SDL_Renderer* renderer, Vector2 pos, AsteroidSize size);

    void Update(float dt) override;
    bool CheckCollision(const Vector2& point) const;
    void SetVelocity(const Vector2& v);
    AsteroidSize GetSize() const;

    float GetRadius() const;

private:
    AsteroidSize sizeType;
    Vector2 velocity;
};
