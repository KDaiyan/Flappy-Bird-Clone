#include "Game.hpp"
#include "Render.hpp"

void Game::beginGame() {
    Render::initializeRenderer();
    startPhase();

    // Primary Game Loop
    while(Render::window.isOpen()) {
        evaluateKeyPress();

        // If first column is out of range, pop it off the deque and add a new one
        if(_columns.front().isColumnOutOfBounds(_bird.getPos().x)) {
            _columns.pop_front();
            _columns.emplace_back(_random(), _columns.back().getUpperColumn().getPosition().x, birdCalcs::columnSeparation);
        }

        // Increment score if bird passed a column
        static Column closestColumn = _bird.getClosestColumn(_columns);
        auto hasClosestColumnChanged = [&](const Column& column) {
            if(closestColumn == column) {
                return false;
            }
            else {
                closestColumn = column;
                return true;
            }
        };

        if(const Column& nearestColumn = _bird.getClosestColumn(_columns);
            hasClosestColumnChanged(nearestColumn) && _bird.hasPassedColumn(nearestColumn)) {
                ++_currentScore;
        }

        // Reset game if bird collides with a column
        if(_bird.isCollision(_columns)) {
            updateBestScore();
            enterRetryMenu();
            resetGame();
            continue;
        }

        // Update the bird
        updateBirdSprite();
        _bird.updateBirdPosition();
        adjustSpeed();

        // Rendering the game
        Render::clear();
        Render::incrementBackGround();
        Render::drawBackground();
        Render::drawScore(_currentScore, _highScore);
        Render::drawBird(_bird);
        std::for_each(_columns.begin(), _columns.end(), [&](Column& Column) {
            Column.moveColumn(_moveSpeed);
            Render::drawColumn(Column);
        });
        Render::onRender();
    }
}

// Method to evaluate key press events
// Returns true for a valid input. This value is only used as an exit condition outside main loop.
bool Game::evaluateKeyPress() {
    for (auto event = sf::Event{}; Render::window.pollEvent(event);) {
        switch(event.type) {
            case sf::Event::KeyPressed: {
                if(event.key.code == sf::Keyboard::Space) {
                    _bird.flap();
                    return true;
                }
            }
            case sf::Event::Closed: {
                Render::close();
                return true;
            }
            default: break;
        }
    }
    return false;
}

void Game::pushInitialColumns() {
    for(int i = 400; i <= 1400; i += 200) {
        _columns.emplace_back(_random(), _bird.getPos().x,static_cast<float>(i));
    }
}

void Game::resetGame() {
    _currentScore = 0;
    _bird = Bird();
    _columns.clear();
    _clock.restart();

    Render::resetBackground();
    pushInitialColumns();
}

void Game::startPhase() {
    _bird.setPos(400.0f);
    while(Render::window.isOpen()) {
        if(evaluateKeyPress()) break;

        updateBirdSprite();
        Render::clear();
        Render::incrementBackGround();
        Render::drawBackground();
        Render::drawBird(_bird);
        Render::drawStartGameText();
        Render::onRender();
    }
    pushInitialColumns();
}
void Game::enterRetryMenu() {
    int increment = 0;
    while(Render::window.isOpen()) {
        if(evaluateKeyPress()) return;

        Render::clear();
        Render::drawBackground();
        Render::drawBird(_bird);
        std::for_each(_columns.begin(), _columns.end(), [&](const Column& column) {
            Render::drawColumn(column);
        });
        Render::drawRetryText(increment, _currentScore, _highScore);
        Render::onRender();
    }
}

void Game::adjustSpeed() {
    // Every six seconds, the speed will increase by 0.2 until it reaches 2.0
    auto incrementSpeed = [&]() {
        return std::clamp(std::floor(_clock.getElapsedTime().asSeconds() / 6.0f) * 0.2f, 0.0f, 2.0f);
    };
    _moveSpeed = std::clamp(1 + incrementSpeed(), 1.0f, 2.0f);
}

void Game::updateBestScore() {
    _highScore = _currentScore > _highScore ? _currentScore : _highScore;
}

void Game::updateBirdSprite() {
    if(_timer.getElapsedTime().asMilliseconds() > 170) {
        _timer.restart();
        Render::animateBird();
    }
}