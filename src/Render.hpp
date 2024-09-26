#pragma once

#include <SFML/Graphics.hpp>
#include "Bird.hpp"

namespace Render {
    inline sf::RenderWindow window;
    inline sf::Font font;
    inline sf::Texture bgTexture, columnTexture, columnRingTexture, birdTexture;
    inline sf::Sprite bgSprite, columnSprite, columnRingSprite, birdSprite;
    inline sf::Text currentScore, bestScore, startGame, retryGame;
    inline unsigned bgIterator = 0;
    inline int birdIterator = 0;

    void initializeRenderer();
    void drawStartGameText();
    void drawRetryText(int& increment, size_t presentScore, size_t bestScore);
    void drawBackground();
    void drawScore(size_t presentScore, size_t topScore);
    void drawColumn(const Column& column);
    void drawBird(const Bird& bird);
    void animateBird();
    void clear();
    void onRender();
    void incrementBackGround();
    void resetBackground();
    void close();
};
