#pragma once

#include <exception>
#include <SFML/Graphics.hpp>

#include "custom_event_queue.hpp"
#include "client.hpp"
#include "resource_provider.hpp"
#include "widget_builder.hpp"

class Game {
public:
    Game(const char*, const char*);
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
private:
    Client m_client;
    sf::RenderWindow m_window;
    ::CustomEventQueue m_customEventQueue;
    ::ResourceProvider m_resourceProvider;
    ::WidgetBuilder m_widgetBuilder;
    std::shared_ptr<Screen::Screen> m_currentScreen;
};
