#pragma once

#include <exception>
#include <SFML/Graphics.hpp>

#include "custom_event_queue.hpp"
#include "client.hpp"
#include "resource_provider.hpp"

class Config;

class Game {
public:
    static const int FPS = 60;
    Game(const char*,
         const char*,
         Connector::Connector&,
         Config&,
         std::size_t = 960,
         std::size_t = 720,
         std::size_t = 2);
    int run();
    void setScreen(std::shared_ptr<Screen::Screen> screen);
    sf::RenderWindow& window() {
        return m_window;
    }
    Client& client() {
        return m_client;
    }

    std::shared_ptr<Screen::Screen> screen() {
        return m_currentScreen;
    }

    std::size_t width() const {
        return m_width;
    }

    std::size_t height() const {
        return m_height;
    }
    
    std::size_t scaleFactor() const {
        return m_scaleFactor;
    }
private:
    Client m_client;
    Config& m_config;
    sf::RenderWindow m_window;
    ::CustomEventQueue& m_customEventQueue;
    ::ResourceProvider& m_resourceProvider;
    std::shared_ptr<Screen::Screen> m_currentScreen;
    std::size_t m_width, m_height;
    std::size_t m_scaleFactor;
};
