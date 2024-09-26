#include "Render.hpp"
#include <array>

void Render::initializeRenderer() {
    window.create(sf::VideoMode(birdCalcs::windowWidth, birdCalcs::windowHeight), "Flappy Birb");
    window.setFramerateLimit(60);

    // Load Background
    bgTexture.loadFromFile("../../assets/Background.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setTextureRect(sf::IntRect(0, 0, birdCalcs::windowWidth, birdCalcs::windowHeight));

    // Load Columns
    columnTexture.loadFromFile("../../assets/Column.png");
    columnSprite.setTexture(columnTexture);
    columnSprite.setTextureRect(sf::IntRect(0, 0, 54, 1));

    columnRingTexture.loadFromFile("../../assets/Column-Ring.png");
    columnRingSprite.setTexture(columnRingTexture);
    columnRingSprite.setTextureRect(sf::IntRect(0, 0, 60, 30));

    // Load Bird
    birdTexture.loadFromFile("../../assets/Bird-Sprite-Sheet.png");
    birdSprite.setTexture(birdTexture);
    birdSprite.setTextureRect(sf::IntRect(birdIterator * birdCalcs::birdWidth, 10, birdCalcs::birdWidth, birdCalcs::birdHeight));

    // Load text
    font.loadFromFile("../../assets/Flappy-Bird.ttf");

    constexpr std::array<sf::Text*, 4> texts = {&currentScore, &retryGame, &bestScore, &startGame};
    int index = 0; // Indexing because first two have different character size

    std::for_each(texts.begin(), texts.end(), [&](sf::Text* text) {
        text->setFont(font);
        text->setCharacterSize(index > 1 ? 60 : 100); // Different character size for first two texts
        text->setFillColor(sf::Color::White);
        text->setOutlineThickness(4);
        text->setOutlineColor(sf::Color::Black);
        index++;
    });
}

void Render::incrementBackGround() {
    bgIterator = (bgIterator + 1) % (bgTexture.getSize().x - 600);
}

void Render::drawBackground() {
    bgSprite.setTextureRect(sf::IntRect(static_cast<int>(bgIterator), 0, birdCalcs::windowWidth, birdCalcs::windowHeight));
    window.draw(bgSprite);
}

void Render::drawBird(const Bird& bird) {
    birdSprite.setPosition(bird.getPos());
    window.draw(birdSprite);
}

void Render::drawColumn(const Column& column) {
    const std::array<sf::RectangleShape, 2> columns = {column.getUpperColumn(), column.getLowerColumn()};

    std::for_each(columns.begin(), columns.end(), [&](const sf::RectangleShape& Column) {
        columnSprite.setPosition(Column.getPosition().x + 3, Column.getPosition().y);
        for(int i = 0; i < static_cast<int>(Column.getSize().y); i++) {
            window.draw(columnSprite);
            columnSprite.move(0, 1);
        }
    });

    // Draw Upper Ring
    columnRingSprite.setPosition(column.getUpperColumn().getPosition().x,
        column.getUpperColumn().getPosition().y + column.getUpperColumn().getSize().y - birdCalcs::columnSize);
    window.draw(columnRingSprite);
    // Draw Lower Ring
    columnRingSprite.setPosition(column.getLowerColumn().getPosition().x, column.getLowerColumn().getPosition().y);
    window.draw(columnRingSprite);
}

void Render::drawStartGameText() {
    startGame.setString("Press Space to begin game!");
    startGame.setPosition(birdCalcs::windowCenterX - 255, 500);
    window.draw(startGame);
}

void Render::drawRetryText(int& increment, const size_t presentScore, const size_t bestScore) {
    // Make a black texture to create a fade in effect
    sf::RectangleShape fade(sf::Vector2f(birdCalcs::windowWidth, birdCalcs::windowHeight));
    fade.setFillColor(sf::Color(0, 0, 0, std::clamp(increment += 3, 100, 180)));
    window.draw(fade);

    retryGame.setFillColor(sf::Color(255, 255, 255, std::clamp(increment += 3, 0, 255)));
    retryGame.setString("  Game Over!\n\n"
                        "Score: " + std::to_string(presentScore) + "\n"
                        "Best Score: " + std::to_string(bestScore) + "\n\n"
                        " Space to retry"
                        );
    retryGame.setPosition(birdCalcs::windowCenterX - 255, 100);
    window.draw(retryGame);
}

void Render::drawScore(const size_t presentScore, const size_t topScore) {
    currentScore.setString(std::to_string(presentScore));
    currentScore.setPosition(birdCalcs::windowCenterX + 15, 30);
    window.draw(currentScore);

    bestScore.setString(std::to_string(topScore));
    bestScore.setPosition(birdCalcs::windowCenterX + 20, 130);
    window.draw(bestScore);
}

void Render::animateBird() {
    // Goes from 0 to 3 (Sprite count - 1). Increments by 1 each time and modulo resets it to 0.
    birdIterator = (birdIterator + 1) % (birdCalcs::birdSpriteCount - 1);
    birdSprite.setTextureRect(sf::IntRect(birdIterator * birdCalcs::birdWidth, 10, birdCalcs::birdWidth, birdCalcs::birdHeight));
}

void Render::clear() {
    window.clear();
}

void Render::onRender() {
    window.display();
}

void Render::resetBackground() {
    bgIterator = 0;
}

void Render::close() {
    window.close();
}