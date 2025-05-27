#include "Asteroid.h"
#include <SDL_image.h>
#include <SDL_log.h>

Asteroid::Asteroid(SDL_Renderer* renderer, Vector2 spawnPos, Vector2 vel)
	: GameObject(renderer), velocity(vel)
{
	position = spawnPos;
	scale = Vector2(1.f, 1.f);
	zRotation = 0.f;

	// Carga la textura, puedes usar la misma que el jugador o una propia
	SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");
	if (!surf) {
		SDL_Log("Error loading asteroid sprite: %s", SDL_GetError());
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, surf);
		SDL_FreeSurface(surf);
	}
}

void Asteroid::Update(float dt) {
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;

	// Rebotar/envolver en pantalla 500x500
	if (position.x < 0) position.x += 500;
	else if (position.x > 500) position.x -= 500;

	if (position.y < 0) position.y += 500;
	else if (position.y > 500) position.y -= 500;

	// Girar lentamente
	zRotation += 30.f * dt;
	if (zRotation >= 360.f) zRotation -= 360.f;
}

void Asteroid::Render(SDL_Renderer* renderer) {
	SDL_Rect src{ 0, 0, 64, 64 };
	SDL_Rect dst{
		static_cast<int>(position.x - 32), // Centrar el dibujo
		static_cast<int>(position.y - 32),
		static_cast<int>(64 * scale.x),
		static_cast<int>(64 * scale.y)
	};
	SDL_Point center = { 32, 32 };

	SDL_RenderCopyEx(renderer, texture, &src, &dst, zRotation, &center, SDL_FLIP_NONE);
}
