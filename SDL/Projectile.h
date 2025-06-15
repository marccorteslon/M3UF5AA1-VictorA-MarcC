#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "UIText.h"

class Scene {
protected:
    SDL_Renderer* renderer;
    std::vector<GameObject*> objects;
    std::vector<UIText*>     textObjects;
    bool                      finished;
    std::string               targetScene;

public:
    virtual void Start(SDL_Renderer* rend) {
        renderer = rend;
        finished = false;
        targetScene = "";
    }

    virtual void Update(float dt) {
        for (auto obj : objects) obj->Update(dt);
    }

    virtual void Render(SDL_Renderer* rend) {
        for (auto obj : objects)    obj->Render(rend);
        for (auto txt : textObjects) txt->Render(rend);
    }

    virtual void Exit() {}

    bool IsFinished() const { return finished; }
    std::string GetTargetScene() const { return targetScene; }

    SDL_Renderer* GetRenderer() const { return renderer; }
};
