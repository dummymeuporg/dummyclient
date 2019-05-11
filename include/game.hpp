#pragma once

#include <exception>
#include <SFML/Graphics.hpp>

#include "client.hpp"

class GameError : public std::exception {

};

class FontLoadingError : public GameError {
    virtual const char* what() const noexcept override {
        return "could not load font";
    }
};

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

    const sf::Font& font(const std::string&);
private:
    Client m_client;
    sf::RenderWindow m_window;
    std::map<std::string, sf::Font> m_fonts;
};
