#pragma once

#include <vector>
#include <SDL.h>
#include "GameObject.h"
#include "Projectile.h"
#include "Utils.h"

class Spaceship : public GameObject {
private:
    SDL_Renderer* renderer_;
    Vector2 velocity;
    float acceleration = 200.0f;
    float maxSpeed = 300.0f;
    float angularVelocity = 0.0f;
    float angularDrag = 0.95f;
    float linearDrag = 0.98f;
    float fireCooldown = 0.0f;
    float fireRate = 0.25f;

    std::vector<Projectile*> projectiles;
    SDL_Renderer* m_renderer;

public:
    Spaceship(SDL_Renderer* renderer);
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    std::vector<Projectile*>& GetProjectiles();
};
