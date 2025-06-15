#include "Projectile.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265f
#endif

Projectile::Projectile(SDL_Renderer* renderer, Vector2 pos, float angle, float speedFactor)
    : GameObject(renderer,
        new Vector2Int(33, 31),
        new Vector2Int(7, 8))
{
    position = pos;
    float radians = (angle - 90.0f) * (M_PI / 180.0f);
    Vector2 dir(std::cos(radians), std::sin(radians));
    velocity = dir * speedFactor;
    zRotation = angle;
}

void Projectile::Update(float dt) {
    position += velocity * dt;
    lifetime -= dt;
}
