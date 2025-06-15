#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utils.h"

class GameObject {
protected:
    Vector2 position;
    Vector2 scale;
    float zRotation;
    SDL_Texture* texture;
    Vector2Int textureCoord;
    Vector2Int size;

public:
    GameObject(SDL_Renderer* renderer, Vector2Int* _textureCoord, Vector2Int* _size);

    virtual void Update(float dt) = 0;
    virtual void Render(SDL_Renderer* renderer);

    Vector2 GetPosition() const { return position; }
    void SetPosition(const Vector2& p) { position = p; }

    float GetRotation() const { return zRotation; }
    void SetRotation(float rot) { zRotation = rot; }

    Vector2 GetScale() const { return scale; }
    void SetScale(const Vector2& s) { scale = s; }

    Vector2Int GetSize() const { return size; }
};
