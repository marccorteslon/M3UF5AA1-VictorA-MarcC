#include "Player.h"
#include <cmath>

constexpr float PI = 3.14159265f;

Player::Player(SDL_Renderer* renderer) : GameObject(renderer) {
    position = Vector2(250.f, 250.f);
    velocity = Vector2(0.f, 0.f);
    rotation = 0.f;
    zRotation = 0.f;
}

void Player::Update(float dt) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // Girar izquierda y derecha (rotación en grados)
    if (keystate[SDL_SCANCODE_LEFT]) {
        rotation -= 180.f * dt;  // 180 grados por segundo hacia la izquierda
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        rotation += 180.f * dt;  // 180 grados por segundo hacia la derecha
    }

    // Limitar rotación a [0, 360)
    if (rotation >= 360.f) rotation -= 360.f;
    if (rotation < 0.f) rotation += 360.f;

    // Aceleración hacia adelante con flecha arriba
    if (keystate[SDL_SCANCODE_UP]) {
        float rad = rotation * PI / 180.f; // convertir grados a radianes
        velocity.x += cos(rad) * 100.f * dt; // acelera con impulso 100
        velocity.y += sin(rad) * 100.f * dt;
    }

    // Limitamos la velocidad para que no se vuelva loca
    float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    const float maxSpeed = 300.f;
    if (speed > maxSpeed) {
        velocity.x = (velocity.x / speed) * maxSpeed;
        velocity.y = (velocity.y / speed) * maxSpeed;
    }

    // Actualizamos posición según la velocidad
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Envolver por pantalla (pantalla 500x500)
    if (position.x < 0) position.x += 500;
    else if (position.x > 500) position.x -= 500;

    if (position.y < 0) position.y += 500;
    else if (position.y > 500) position.y -= 500;

    // Actualizamos rotación para el render
    zRotation = rotation;
}

void Player::Render(SDL_Renderer* renderer) {
    SDL_Rect src{ 0, 0, 30, 40 };
    SDL_Rect dst{
        static_cast<int>(position.x - src.w / 2),
        static_cast<int>(position.y - src.h / 2),
        src.w,
        src.h
    };
    SDL_Point center = { src.w / 2, src.h / 2 };
    SDL_RenderCopyEx(renderer, texture, &src, &dst, zRotation, &center, SDL_FLIP_NONE);
}
