#include "HighscoreManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>

std::vector<ScoreEntry> HighscoreManager::LoadScores() {
    std::vector<ScoreEntry> scores;
    std::ifstream file("highscores.txt");

    if (!file) return scores;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        int score;
        if (ss >> name >> score) {
            scores.push_back({ name, score });
        }
    }

    return scores;
}

std::vector<ScoreEntry> HighscoreManager::GetTopScores(int limit) {
    auto scores = LoadScores();
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
        });

    if (scores.size() > limit) {
        scores.resize(limit);
    }

    return scores;
}

void HighscoreManager::AddScore(const std::string& name, int score) {
    auto scores = LoadScores();
    scores.push_back({ name, score });
    SaveScores(scores);
}

void HighscoreManager::SaveScores(const std::vector<ScoreEntry>& scores) {
    std::ofstream file("highscores.txt");

    for (const auto& entry : scores) {
        file << entry.name << " " << entry.score << "\n";
    }
}
