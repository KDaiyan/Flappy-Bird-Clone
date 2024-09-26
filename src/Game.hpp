#pragma once

#include "Column.hpp"
#include "Bird.hpp"
#include <deque>
#include <random>

class Game {
private:
    Bird _bird;
    std::deque<Column> _columns;
    size_t _highScore = 0;
    size_t _currentScore = 0;
    sf::Clock _clock, _timer;
    float _moveSpeed = 1;

    struct randomizer {
        std::random_device dev;
        std::mt19937 rng;
        std::uniform_int_distribution<std::mt19937::result_type> dist;

        randomizer() : rng(dev()), dist(100, 650) {}
        unsigned operator()() { return dist(rng); }
    } _random;

    bool evaluateKeyPress();
    void updateBirdSprite();
    void pushInitialColumns();
    void updateBestScore();
    void resetGame();
    void startPhase();
    void adjustSpeed();
    void enterRetryMenu();

public:
    void beginGame();
};