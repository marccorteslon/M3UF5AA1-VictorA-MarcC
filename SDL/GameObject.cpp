#include "GameObject.h"
#include <SDL_image.h>    
#include <iostream>       

GameObject::GameObject(SDL_Renderer* renderer, Vector2Int* _textureCoord, Vector2Int* _size)
    : texture(nullptr)
{
    position = Vector2(0, 0);
    zRotation = 0.f;
    scale = Vector2(1.f, 1.f);

    textureCoord = *_textureCoord;
    size = *_size;

    SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");
    if (!surf) {
        std::cout << "[ ERROR ] - No es pot carregar la superfície: " << SDL_GetError() << std::endl;
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (!texture) {
            std::cout << "[ ERROR ] - No es pot crear la textura: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(surf);
    }
}

void GameObject::Render(SDL_Renderer* renderer) {
    if (!texture) return;

    SDL_Rect source{
        textureCoord.x,
        textureCoord.y,
        size.x,
        size.y
    };

    SDL_Rect dest{
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(size.x * scale.x),
        static_cast<int>(size.y * scale.y)
    };

    SDL_RenderCopyEx(renderer, texture, &source, &dest, zRotation, nullptr, SDL_FLIP_NONE);
}
