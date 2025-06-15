#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Utils.h"

class UIText {
private:
    Vector2 position;
    Vector2 scale;
    float zRotation;

    SDL_Texture* texture;
    int width;
    int height;

    int fontSize;
    std::string fontPath;

    std::string text;

    void GenerateTexture(SDL_Renderer* rend);

public:
    UIText(SDL_Renderer* rend, Vector2 pos, Vector2 initScale, float initzRotation, std::string textToPrint, int initFontSize = 28);
    ~UIText();

    void Update(float dt);
    void Render(SDL_Renderer* rend);
    void SetText(std::string newText, SDL_Renderer* rend);


    Vector2 GetPosition() const { return position; }
    void SetPosition(const Vector2& pos) { position = pos; }
    Vector2 GetScale() const { return scale; }
    std::string GetText() const { return text; }
};
