#pragma once
#include <vector>
#include <string>

struct ScoreEntry {
    std::string name;
    int score = 0;
};

class HighscoreManager {
public:
    void AddScore(const std::string& name, int score);
    std::vector<ScoreEntry> LoadScores();
    std::vector<ScoreEntry> GetTopScores(int limit);
    void SaveScores(const std::vector<ScoreEntry>& scores);
};
