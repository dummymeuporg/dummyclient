#pragma once

#include <SFML/Graphics.hpp>

class Client;

namespace Screen {

class Screen {
public:
    Screen(sf::RenderWindow&, ::Client&);
    virtual void notify() = 0;
    virtual void draw() = 0;

protected:
    sf::RenderWindow& m_window;
    ::Client& m_client;
};

} // namespace Screen
