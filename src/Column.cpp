#include "Column.hpp"
#include "Bird.hpp"

Column::Column(const int center, const float ballXPosition, const float distanceFromBall) {
    _lowerColumnCeiling = (center + birdCalcs::openingSize / 2 > 800) ? 800 : center + birdCalcs::openingSize / 2;
    _upperColumnFloor = (center - birdCalcs::openingSize / 2 < 0) ? 0 : center - birdCalcs::openingSize / 2;

    _upperColumn.setSize(sf::Vector2f(60.0f, static_cast<float>(_upperColumnFloor)));
    _upperColumn.setPosition(ballXPosition + distanceFromBall, 0);
    _lowerColumn.setSize(sf::Vector2f(60.0f, 800.0f - static_cast<float>(_lowerColumnCeiling)));
    _lowerColumn.setPosition(ballXPosition + distanceFromBall, static_cast<float>(_lowerColumnCeiling));
}

const sf::RectangleShape& Column::getUpperColumn() const {
    return _upperColumn;
}

const sf::RectangleShape& Column::getLowerColumn() const {
    return _lowerColumn;
}

void Column::moveColumn(const float speed) {
    _upperColumn.move(-speed, 0);
    _lowerColumn.move(-speed, 0);
}

bool Column::isColumnOutOfBounds(const float ballXPosition) const {
    return _upperColumn.getPosition().x - ballXPosition <= -400;
}

bool Column::operator==(const Column& other) const {
    // This is sufficient for the purposes of the game, but realistically it's not a complete comparison
    return this->getLowerColumn().getSize() == other.getLowerColumn().getSize() &&
           this->getLowerColumn().getLocalBounds() == other.getLowerColumn().getLocalBounds();
}