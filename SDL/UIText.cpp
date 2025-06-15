#include "UIText.h"

UIText::UIText(SDL_Renderer* rend, Vector2 pos, Vector2 initScale, float initzRotation, std::string textToPrint, int initFontSize)
    : position(pos), scale(initScale), zRotation(initzRotation), text(textToPrint), fontSize(initFontSize), fontPath("resources/PixelPowerline-9xOK.ttf") {
    GenerateTexture(rend);
}

UIText::~UIText() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void UIText::GenerateTexture(SDL_Renderer* rend) {
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cout << "[ ERROR ] - Font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);

    if (!surf) {
        std::cout << "[ ERROR ] - Surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    texture = SDL_CreateTextureFromSurface(rend, surf);
    if (!texture) {
        std::cout << "[ ERROR ] - Texture: " << SDL_GetError() << std::endl;
    }

    width = surf->w;
    height = surf->h;

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
}

void UIText::Update(float dt) {

}

void UIText::Render(SDL_Renderer* rend) {
    if (!texture) return;

    SDL_Rect dest;
    dest.w = static_cast<int>(width * scale.x);
    dest.h = static_cast<int>(height * scale.y);
    dest.x = static_cast<int>(position.x - dest.w / 2.0f);
    dest.y = static_cast<int>(position.y - dest.h / 2.0f);

    SDL_RenderCopyEx(rend, texture, nullptr, &dest, zRotation, nullptr, SDL_FLIP_NONE);
}

void UIText::SetText(std::string newText, SDL_Renderer* rend) {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    text = newText;
    GenerateTexture(rend);
}
