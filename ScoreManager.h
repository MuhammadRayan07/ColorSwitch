#pragma once
#include <fstream>
#include <string>
#include <stdexcept>

class ScoreManager
{
private:
    int score = 0;
    int highScore = 0;
    const std::string filename = "highscore.txt";

public:
    void increment() { score++; }
    int  getScore()     const { return score; }
    int  getHighScore() const { return highScore; }
    void reset() { score = 0; }

    void load()
    {
        try
        {
            std::ifstream file(filename);
            if (!file.is_open())
                throw std::runtime_error("Could not open highscore file for reading");
            file >> highScore;
            if (file.fail())
                throw std::runtime_error("Highscore file is corrupted or empty");
        }
        catch (const std::runtime_error&)
        {
            highScore = 0;
        }
    }

    void save()
    {
        try
        {
            if (score > highScore)
                highScore = score;
            std::ofstream file(filename);
            if (!file.is_open())
                throw std::runtime_error("Could not open highscore file for writing");
            file << highScore;
        }
        catch (const std::runtime_error&)
        {
            // meow meow
        }
    }
};