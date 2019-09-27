#pragma once

#include <SFML/Graphics.hpp>

namespace Screen {

class GameScreen;

namespace GameScreenState {

class State {
public:
    State(GameScreen&);
    virtual ~State();
    virtual void draw(sf::RenderWindow&) = 0;
    virtual void tick() = 0;
protected:
    GameScreen& m_gameScreen;
};

} // namespace GameScreenState
} // namespace Screen
