#pragma once

#include "Scene.h"
#include "Spaceship.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "UIText.h"
#include <vector>

class GameplayScene : public Scene {
public:
    void Start(SDL_Renderer* rend) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* rend) override;
    void Exit() override;

private:
    void SpawnAsteroids(int count);
    void SpawnEnemy();

    std::vector<Asteroid*> asteroids;
    std::vector<Enemy*>    enemies;
    std::vector<UIText*>   textObjects;

    UIText* scoreText = nullptr;
    UIText* livesText = nullptr;
    float asteroidTimer = 0.0f;

    float enemyTimer = 0.0f;
    int   lives = 3;
    int   score = 0;
};
