#include "GameplayScene.h"
#include "Spaceship.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "Enemy.h"
#include "HighscoreManager.h"
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <random>

static constexpr int SCREEN_WIDTH = 500;
static constexpr int SCREEN_HEIGHT = 500;

void GameplayScene::Start(SDL_Renderer* rend) {
    Scene::Start(rend);
    lives = 3;
    score = 0;
    enemyTimer = 0.0f;

    objects.push_back(new Spaceship(rend));
    SpawnAsteroids(5);

    scoreText = new UIText(rend, Vector2(60, 20), Vector2(1, 1), 0.0f, "Score: 0", 24);
    livesText = new UIText(rend, Vector2(450, 20), Vector2(1, 1), 0.0f, "Lives: 3", 24);
    textObjects.push_back(scoreText);
    textObjects.push_back(livesText);
}

void GameplayScene::Update(float dt) {
    Scene::Update(dt);

    {
        std::ostringstream ss;
        ss << "Score: " << score;
        scoreText->SetText(ss.str(), renderer);
    }
    {
        std::ostringstream ss;
        ss << "Lives: " << lives;
        livesText->SetText(ss.str(), renderer);
    }

    enemyTimer += dt;
    asteroidTimer += dt;

    if (enemyTimer >= 15.0f) {
        SpawnEnemy();
        enemyTimer = 0.0f;
    }

    if (asteroidTimer >= 12.0f) {
        SpawnAsteroids(1);
        asteroidTimer = 0.0f;
    }

    Spaceship* ship = nullptr;
    for (auto* o : objects) {
        if ((ship = dynamic_cast<Spaceship*>(o))) break;
    }
    if (!ship) return;

    auto& projs = ship->GetProjectiles();

    for (int i = 0; i < projs.size(); ) {
        bool removed = false;
        for (int j = 0; j < asteroids.size(); ) {
            if (asteroids[j]->CheckCollision(projs[i]->GetPosition())) {
                AsteroidSize sz = asteroids[j]->GetSize();
                Vector2 posAst = asteroids[j]->GetPosition();

                delete asteroids[j];
                objects.erase(std::remove(objects.begin(), objects.end(), asteroids[j]), objects.end());
                asteroids.erase(asteroids.begin() + j);

                int count = 0;
                AsteroidSize newSize;
                float speedBase;

                if (sz == BIG) {
                    newSize = MEDIUM;
                    count = 2;
                    speedBase = 60.0f;
                }
                else if (sz == MEDIUM) {
                    newSize = SMALL;
                    count = 2;
                    speedBase = 80.0f;
                }

                if (count > 0) {
                    for (int k = 0; k < count; ++k) {
                        float angle = ((rand() % 360) + k * 180) * (M_PI / 180.0f);
                        Vector2 offset = Vector2(std::cos(angle), std::sin(angle)) * 10.0f;
                        Vector2 spawnPos = posAst + offset;
                        Vector2 dir = offset.Normalized();

                        Asteroid* newAst = new Asteroid(renderer, spawnPos, newSize);
                        newAst->SetVelocity(dir * (speedBase + rand() % 30));
                        asteroids.push_back(newAst);
                        objects.push_back(newAst);
                    }
                }

                score += (sz == BIG ? 50 : sz == MEDIUM ? 30 : 20);

                delete projs[i];
                projs.erase(projs.begin() + i);
                removed = true;
                break;
            }
            else {
                ++j;
            }
        }
        if (!removed) ++i;
    }

    for (int i = 0; i < projs.size(); ) {
        bool removed = false;
        for (int j = 0; j < enemies.size(); ) {
            if (enemies[j]->CheckCollision(projs[i]->GetPosition())) {
                delete enemies[j];
                objects.erase(std::remove(objects.begin(), objects.end(), enemies[j]), objects.end());
                enemies.erase(enemies.begin() + j);
                delete projs[i];
                projs.erase(projs.begin() + i);
                score += 150;
                removed = true;
                break;
            }
            else {
                ++j;
            }
        }
        if (!removed) ++i;
    }

    for (auto* e : enemies) {
        if (e->CheckCollision(ship->GetPosition())) {
            --lives;
            ship->SetPosition(Vector2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
            if (lives <= 0) {
                HighscoreManager hs;
                hs.AddScore("Player", score);
                finished = true;
                targetScene = "Highscores";
            }
            break;
        }
    }
    for (auto* a : asteroids) {
        if (a->CheckCollision(ship->GetPosition())) {
            std::cout << "Asteroide ha col·lisionat amb la nau!" << std::endl;
            --lives;
            ship->SetPosition(Vector2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
            if (lives <= 0) {
                HighscoreManager hs;
                hs.AddScore("Player", score);
                finished = true;
                targetScene = "Highscores";
            }
            break;
        }
    }
}

void GameplayScene::Render(SDL_Renderer* rend) {
    Scene::Render(rend);
    for (auto* t : textObjects) t->Render(rend);
}

void GameplayScene::Exit() {
    for (auto* o : objects)    delete o;
    for (auto* t : textObjects) delete t;
    objects.clear();
    asteroids.clear();
    enemies.clear();
    textObjects.clear();
}

void GameplayScene::SpawnAsteroids(int count) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159265f);
    float screenCenterX = SCREEN_WIDTH / 2.0f;
    float screenCenterY = SCREEN_HEIGHT / 2.0f;
    float spawnRadius = std::sqrt(screenCenterX * screenCenterX + screenCenterY * screenCenterY) + 50.0f;

    const float minDistance = 90.0f;
    int generated = 0;
    int attempts = 0;
    const int maxAttempts = 300;

    while (generated < count && attempts < maxAttempts) {
        float angle = angleDist(rng);
        Vector2 pos(
            screenCenterX + std::cos(angle) * spawnRadius,
            screenCenterY + std::sin(angle) * spawnRadius
        );

        bool overlaps = false;
        for (auto* a : asteroids) {
            if ((a->GetPosition() - pos).Magnitude() < minDistance) {
                overlaps = true;
                break;
            }
        }

        if (overlaps) {
            ++attempts;
            continue;
        }

        Asteroid* a = new Asteroid(renderer, pos, BIG);
        Vector2 direction = Vector2(screenCenterX, screenCenterY) - pos;
        a->SetVelocity(direction.Normalized() * (50.0f + std::rand() % 50));

        asteroids.push_back(a);
        objects.push_back(a);
        ++generated;
    }

    if (attempts >= maxAttempts) {
        std::cout << "No s'han pogut generar tots els asteroides separats\n";
    }
}

void GameplayScene::SpawnEnemy() {
    Vector2 pos(float(std::rand() % SCREEN_WIDTH), float(std::rand() % SCREEN_HEIGHT));
    auto* e = new Enemy(renderer, pos);
    enemies.push_back(e);
    objects.push_back(e);
}
