#include "Spaceship.h"
#include "InputManager.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265f
#endif

Spaceship::Spaceship(SDL_Renderer* renderer)
    : GameObject(renderer,
        new Vector2Int(0, 0),
        new Vector2Int(30, 40)),
    m_renderer(renderer)
{
    position = Vector2(250.0f, 250.0f);
}

void Spaceship::Update(float dt) {

    const float rotationSpeed = 250.0f;
    if (IM.GetKey(SDLK_RIGHT, DOWN) || IM.GetKey(SDLK_RIGHT, HOLD))
        zRotation += rotationSpeed * dt;
    if (IM.GetKey(SDLK_LEFT, DOWN) || IM.GetKey(SDLK_LEFT, HOLD))
        zRotation -= rotationSpeed * dt;

    float rad = (zRotation - 90.0f) * (M_PI / 180.0f);
    Vector2 dir(std::cos(rad), std::sin(rad));

    if (IM.GetKey(SDLK_UP, DOWN) || IM.GetKey(SDLK_UP, HOLD))
        velocity += dir * acceleration * dt;

    velocity = velocity * std::pow(linearDrag, dt * 60.0f);
    if (velocity.Magnitude() > maxSpeed)
        velocity = velocity.Normalized() * maxSpeed;

    position += velocity * dt;

    if (position.x < 0)   position.x = 500;
    if (position.x > 500) position.x = 0;
    if (position.y < 0)   position.y = 500;
    if (position.y > 500) position.y = 0;

    fireCooldown -= dt;
    if ((IM.GetKey(SDLK_SPACE, DOWN) || IM.GetKey(SDLK_SPACE, HOLD)) && fireCooldown <= 0.0f) {
        const float bulletSpeed = 400.0f;
        projectiles.push_back(
            new Projectile(m_renderer, position, zRotation, bulletSpeed)
        );
        fireCooldown = fireRate;
    }

    for (size_t i = 0; i < projectiles.size(); ) {
        projectiles[i]->Update(dt);
        if (!projectiles[i]->IsAlive()) {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
        else {
            ++i;
        }
    }
}

void Spaceship::Render(SDL_Renderer* renderer) {

    GameObject::Render(renderer);
    for (auto* p : projectiles)
        p->Render(renderer);
}


std::vector<Projectile*>& Spaceship::GetProjectiles() {
    return projectiles;
}