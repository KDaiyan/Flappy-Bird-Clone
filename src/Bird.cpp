#include "Bird.hpp"
#include "Render.hpp"

Bird::Bird() : _birdVelocity(0.0f) {
    _birdPosition = static_cast<float>(Render::bgTexture.getSize().y) / 2;
    _bird.setSize(sf::Vector2f(45, 45)); // Reduced from 64, 50
    _bird.setPosition(birdCalcs::windowCenterX, static_cast<float>(Render::window.getSize().y)/2);
}

const sf::Vector2f& Bird::getPos() const {
    return _bird.getPosition();
}

// Updates bird position based on velocity and acceleration
void Bird::updateBirdPosition() {
    // y_new = y_old * v * dt
    _birdPosition = _birdPosition + _birdVelocity * birdCalcs::dt;
    // v_new  = v_old + a * dt
    _birdVelocity = _birdVelocity + birdCalcs::acceleration * birdCalcs::dt;

    // Clamp bird position between 0 and 800. If clamping is needed, reset velocity to 0.
    _birdPosition > 800 || _birdPosition < 0 ? _birdVelocity = 0 : _birdVelocity;
    _birdPosition = std::clamp(_birdPosition, 0.0f, 800.0f);

    // Set the position
    _bird.setPosition(birdCalcs::windowCenterX, _birdPosition);
}

void Bird::setPos(const float pos) {
    _birdPosition = pos;
    _bird.setPosition(birdCalcs::windowCenterX, _birdPosition);
}

// Accelerates the bird upwards
void Bird::flap() {
    _birdVelocity = -birdCalcs::jumpVelocity;
}

// Uses AABB Collision to check if the bird has collided with a column
bool Bird::isCollision(const std::deque<Column>& columns) const {
    // If bird hit the floor, it's already a collision
    if(_bird.getPosition().y + _bird.getSize().y >= birdCalcs::windowHeight) return true;

    // Lambda function to check if bird intersects with a column
    auto predicate = [&](const Column& column) -> bool {
        return _bird.getGlobalBounds().intersects(column.getLowerColumn().getGlobalBounds()) ||
               _bird.getGlobalBounds().intersects(column.getUpperColumn().getGlobalBounds());
    };
    return std::any_of(columns.begin(), columns.end(), predicate);
}

// Returns the closest column that the bird should pass through
Column Bird::getClosestColumn(const std::deque<Column>& columns) const {
    Column closestColumn = columns.front();
    float distance = closestColumn.getUpperColumn().getPosition().x - birdCalcs::windowCenterX;
    distance < 0 ? distance = 1000 : distance; // Arbitrary out of range number as invalid distance

    std::for_each(columns.begin(), columns.end(), [&](const Column& column) {
        if(const auto currentDistance = column.getUpperColumn().getPosition().x - birdCalcs::windowCenterX;
            currentDistance < distance && currentDistance > 0) {
                closestColumn = column;
                distance = currentDistance;
        }
    });
    return closestColumn;
}

// Returns a boolean determining if the bird has passed a column
bool Bird::hasPassedColumn(const Column& column) const {
    // 300 distance check to prevent counting initial column
    return std::abs(_bird.getPosition().x + _bird.getSize().x - column.getUpperColumn().getPosition().x) <= 300 &&
            _bird.getPosition().x + _bird.getSize().x <=  column.getUpperColumn().getPosition().x;
}