#include "MenuScenes.h"
#include <SDL.h>

void MenuScene::Start(SDL_Renderer* rend) {
    Scene::Start(rend);
    textObjects.clear();
    options.clear();

    title = new UIText(renderer, Vector2(250.0f, 100.0f), Vector2(1.5f, 1.5f), 0.0f, "ASTEROIDS", 48);
    author = new UIText(renderer, Vector2(250.0f, 150.0f), Vector2(1.0f, 1.0f), 0.0f, "Alexandre Fernandez", 20);
    textObjects.push_back(title);
    textObjects.push_back(author);

    options.push_back(new UIText(renderer, Vector2(250.0f, 220.0f), Vector2(1.0f, 1.0f), 0.0f, "Start Game", 32));
    options.push_back(new UIText(renderer, Vector2(250.0f, 270.0f), Vector2(1.0f, 1.0f), 0.0f, "Highscores", 32));
    options.push_back(new UIText(renderer, Vector2(250.0f, 320.0f), Vector2(1.0f, 1.0f), 0.0f, "Salir", 32));

    for (auto* o : options) textObjects.push_back(o);

    cursor = new UIText(renderer, Vector2(150.0f, 220.0f), Vector2(1.0f, 1.0f), 0.0f, ">", 32);
    textObjects.push_back(cursor);

    UpdateCursorPosition();
}

void MenuScene::Update(float dt) {
    Scene::Update(dt);

    if (IM.GetKey(SDLK_DOWN, KeyState::DOWN)) {
        selectedIndex = (selectedIndex + 1) % options.size();
        UpdateCursorPosition();
    }
    else if (IM.GetKey(SDLK_UP, KeyState::DOWN)) {
        selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
        UpdateCursorPosition();
    }


    for (int i = 0; i < options.size(); ++i) {
        if (IsMouseOver(options[i])) {
            selectedIndex = i;
            UpdateCursorPosition();
            if (IM.GetLeftClick()) break;
        }
    }

    if (IM.GetKey(SDLK_RETURN, KeyState::DOWN) || IM.GetLeftClick()) {
        switch (selectedIndex) {
        case 0:
            finished = true;
            targetScene = "Gameplay";
            break;
        case 1:
            finished = true;
            targetScene = "Highscores";
            break;
        case 2:
            IM.Listen();
            SDL_Event quitEvent;
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
            break;
        }
    }
}

void MenuScene::UpdateCursorPosition() {
    if (cursor && selectedIndex >= 0 && selectedIndex < options.size()) {
        Vector2 pos = options[selectedIndex]->GetPosition();
        cursor->SetPosition(Vector2(pos.x - 100.0f, pos.y));
    }
}

bool MenuScene::IsMouseOver(UIText* text) {
    Vector2Int mouse = IM.GetMousePos();
    Vector2 pos = text->GetPosition();
    float width = text->GetText().length() * 16 * text->GetScale().x;
    float height = 32 * text->GetScale().y;
    return mouse.x >= pos.x - width / 2 && mouse.x <= pos.x + width / 2 &&
        mouse.y >= pos.y - height / 2 && mouse.y <= pos.y + height / 2;
}

void MenuScene::Render(SDL_Renderer* rend) {
    Scene::Render(rend);
}

void MenuScene::Exit() {
    for (auto* t : textObjects) delete t;
    textObjects.clear();
    options.clear();
}
