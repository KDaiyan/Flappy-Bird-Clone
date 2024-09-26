#pragma once

#include "Column.hpp"
#include <SFML/Graphics.hpp>
#include <deque>

// Various constants used in calculations
namespace birdCalcs {
    inline constexpr int openingSize = 200;
    inline constexpr int windowHeight = 800;
    inline constexpr int windowWidth = 600;
    inline constexpr int columnSize = 30;
    inline constexpr int birdSpriteCount = 4;
    inline constexpr int birdWidth = 64;
    inline constexpr int birdHeight = 50;
    inline constexpr float acceleration = 30.0f;
    inline constexpr float jumpVelocity = 75.0f;
    inline constexpr float windowCenterX = 275.0f;
    inline constexpr float collisionCheckRange = 60.0f;
    inline constexpr float columnSeparation = 200.0f;
    inline constexpr float dt = 0.15f;
}

class Bird {
private:
    float _birdPosition, _birdVelocity;
    sf::RectangleShape _bird;
public:
    Bird();
    const sf::Vector2f& getPos() const;
    void setPos(float pos);
    void updateBirdPosition();
    void flap();
    bool isCollision(const std::deque<Column>& columns) const;
    bool hasPassedColumn(const Column& column) const;
    Column getClosestColumn(const std::deque<Column>& columns) const;
};