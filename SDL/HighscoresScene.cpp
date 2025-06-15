#include "HighscoresScene.h"
#include "HighscoreManager.h"
#include "InputManager.h"

void HighscoreScene::Start(SDL_Renderer* rend) {
    Scene::Start(rend);

    HighscoreManager manager;
    auto scores = manager.LoadScores();

    textObjects.clear();

    textObjects.push_back(
        new UIText(renderer,
            Vector2(250.0f, 30.0f),
            Vector2(1.0f, 1.0f),
            0.0f,
            "HIGHSCORES",
            36)
    );

    for (int i = 0; i < scores.size(); ++i) {
        UIText* entry = new UIText(renderer,
            Vector2(250.0f, 80 + i * 30),
            Vector2(1.0f, 1.0f),
            0.0f,
            scores[i].name + " - " + std::to_string(scores[i].score),
            20);
        textObjects.push_back(entry);
    }

    UIText* backText = new UIText(renderer,
        Vector2(250.0f, 450.0f),
        Vector2(1.0f, 1.0f),
        0.0f,
        "Click to return to menu",
        18);
    textObjects.push_back(backText);
}

void HighscoreScene::Update(float dt) {
    Scene::Update(dt);

    Vector2Int mouse = IM.GetMousePos();
    if (IM.GetLeftClick()) {
        finished = true;
        targetScene = "MainMenu";
    }
}

void HighscoreScene::Render(SDL_Renderer* rend) {
    Scene::Render(rend);
    for (auto* t : textObjects) t->Render(rend);
}

void HighscoreScene::Exit() {
    for (auto t : textObjects) delete t;
    textObjects.clear();
}
