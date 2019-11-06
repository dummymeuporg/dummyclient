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
         bool = false,
         std::size_t = 960,
         std::size_t = 720,
         std::size_t = 2
         );
    int run();
    sf::RenderWindow& window() {
        return m_window;
    }
    Client& client() {
        return m_client;
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

    std::size_t windowWidth() const {
        return m_windowWidth;
    }

    std::size_t windowHeight() const {
        return m_windowHeight;
    }

    void quit();
private:
    bool m_isFullscreen;
    Client m_client;
    sf::RenderWindow m_window;
    ::CustomEventQueue& m_customEventQueue;
    ::ResourceProvider& m_resourceProvider;
    std::size_t m_width, m_height;
    std::size_t m_windowWidth, m_windowHeight;
    std::size_t m_scaleFactor;
    bool m_isRunning;

};
