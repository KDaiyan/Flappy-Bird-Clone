#pragma once

#include "SFML/Graphics.hpp"

class Column {
private:
    int _upperColumnFloor, _lowerColumnCeiling;
    sf::RectangleShape _upperColumn, _lowerColumn;

public:
    Column(int center, float ballXPosition, float distanceFromBall);
    const sf::RectangleShape& getUpperColumn() const;
    const sf::RectangleShape& getLowerColumn() const;
    bool operator==(const Column& other) const;
    void moveColumn(float speed);
    bool isColumnOutOfBounds(float ballXPosition) const;
};
