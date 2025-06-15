#include "Enemy.h"
#include <cstdlib>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265f
#endif

Enemy::Enemy(SDL_Renderer* renderer, Vector2 pos)
    : GameObject(renderer, new Vector2Int(128, 22), new Vector2Int(19, 21))
{
    position = pos;
    float angle = (rand() % 360) * (M_PI / 180.0f);
    float speed = 100.0f;
    velocity = Vector2(std::cos(angle), std::sin(angle)) * speed;
}

void Enemy::Update(float dt) {
    changeDirTimer -= dt;
    if (changeDirTimer <= 0.0f) {
        float angle = (rand() % 360) * (M_PI / 180.0f);
        float speed = velocity.Magnitude();
        velocity = Vector2(std::cos(angle), std::sin(angle)) * speed;
        changeDirTimer = 1.0f;
    }
    position += velocity * dt;

    if (position.x < 0)   position.x = 500;
    if (position.x > 500) position.x = 0;
    if (position.y < 0)   position.y = 500;
    if (position.y > 500) position.y = 0;
}

bool Enemy::CheckCollision(const Vector2& point) const {
    float dx = position.x - point.x;
    float dy = position.y - point.y;
    float dist = std::sqrt(dx * dx + dy * dy);
    float radius = (size.x * scale.x) / 2.0f;
    return dist < radius;
}
