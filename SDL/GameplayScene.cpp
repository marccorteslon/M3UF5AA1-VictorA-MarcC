#include "GameplayScene.h"
#include "Player.h"

void GameplayScene::Start(SDL_Renderer* rend) {
    Scene::Start(rend);
    objects.push_back(new Player(rend)); // ahora funciona porque Player IS-A GameObject
}

void GameplayScene::Update(float dt) {
    Scene::Update(dt);
}

void GameplayScene::Render(SDL_Renderer* rend) {
    Scene::Render(rend);
}

void GameplayScene::Exit() {
    for (auto obj : objects) {
        delete obj;
    }
    objects.clear();
}
