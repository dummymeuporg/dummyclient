#pragma once

#include <exception>
#include <SFML/Graphics.hpp>

#include "client.hpp"

class Game {
public:
    Game(const char*, const char*);
    int run();
    sf::RenderWindow& window() {
        return m_window;
    }
    Client& client() {
        return m_client;
    }
private:
    Client m_client;
    sf::RenderWindow m_window;
};
