#pragma once
#include "Scene.h"
#include "UIText.h"
#include <vector>

class HighscoreScene : public Scene {
private:
    std::vector<UIText*> scoreTexts;

public:
    void Start(SDL_Renderer* rend) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* rend) override;
    void Exit() override;
};
