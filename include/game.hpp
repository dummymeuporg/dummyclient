#pragma once

#include <SFML/Graphics.hpp>

#include "client.hpp"

class Game {
public:
    Game(const char*, const char*);
    int run();
    sf::RenderWindow& window() {
        return m_window;
    }
private:
    Client m_client;
    sf::RenderWindow m_window;
};
