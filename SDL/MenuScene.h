#pragma once
#include "Scene.h"
#include "UIText.h"
#include "InputManager.h"

class MenuScene : public Scene {
private:
    std::vector<UIText*> options;
    int selectedIndex = 0;
    UIText* cursor;
    UIText* title;
    UIText* author;

public:
    void Start(SDL_Renderer* rend) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* rend) override;
    void Exit() override;

private:
    void UpdateCursorPosition();
    bool IsMouseOver(UIText* text);
};
