#include "Asteroid.h"
#include <cmath>
#include <cstdlib>

static const Vector2Int bigCoords[] = { {156,  0}, {  0, 52}, { 78, 52} };
static const Vector2Int bigSizes[] = { { 97, 91}, { 73, 71}, { 73, 73} };
static const Vector2Int medCoords[] = { { 41,  3}, { 82,  2} };
static const Vector2Int medSizes[] = { { 39, 36}, { 42, 38} };
static const Vector2Int smallCoords[] = { {128, 1}, {128, 22}, {166, 105} };
static const Vector2Int smallSizes[] = { {19, 18}, {19, 21}, {21, 18} };

Asteroid::Asteroid(SDL_Renderer* renderer, Vector2 pos, AsteroidSize size)
    : GameObject(renderer,
        new Vector2Int(
            size == BIG ? bigCoords[rand() % 3] :
            size == MEDIUM ? medCoords[rand() % 2] :
            smallCoords[rand() % 3]
        ),
        new Vector2Int(
            size == BIG ? bigSizes[rand() % 3] :
            size == MEDIUM ? medSizes[rand() % 2] :
            smallSizes[rand() % 3]
        )
    ), sizeType(size)
{
    position = pos;
    velocity = Vector2(0.0f, 0.0f);
    scale = Vector2(1.0f, 1.0f);
    zRotation = 0.0f;
}

void Asteroid::Update(float dt) {
    position += velocity * dt;

    if (position.x < 0)   position.x = 500;
    if (position.x > 500) position.x = 0;
    if (position.y < 0)   position.y = 500;
    if (position.y > 500) position.y = 0;
}

void Asteroid::SetVelocity(const Vector2& v) {
    velocity = v;
}

AsteroidSize Asteroid::GetSize() const {
    return sizeType;
}

float Asteroid::GetRadius() const {
    float baseRadius;
    switch (sizeType) {
    case BIG:    baseRadius = 45.0f; break;
    case MEDIUM: baseRadius = 25.0f; break;
    case SMALL:  baseRadius = 12.0f; break;
    }
    return baseRadius * (scale.x > scale.y ? scale.x : scale.y); //NO TOCAR, funciona
}

bool Asteroid::CheckCollision(const Vector2& point) const {
    float dist = (position - point).Magnitude();
    return dist < GetRadius();
}
