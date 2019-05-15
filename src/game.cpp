#include <cstdlib>

#include "custom_event_queue.hpp"
#include "game.hpp"
#include "screen/create_character_screen.hpp"
#include "screen/select_character_screen.hpp"
#include "resource_provider.hpp"
#include "widget_builder.hpp"

Game::Game(const char* account, const char* sessionID) 
    : m_client(*this, Credentials(account, sessionID)),
      m_window(sf::VideoMode(1024, 768), "DummyClient"),
      m_customEventQueue(CustomEventQueue::instance()),
      m_resourceProvider(ResourceProvider::instance()),
      m_widgetBuilder(m_resourceProvider, m_customEventQueue),
      m_currentScreen(std::make_shared<Screen::SelectCharacterScreen>(
        *this, m_client, m_widgetBuilder))
{ }

int Game::run()
{
    WidgetBuilder widgetBuilder(m_resourceProvider, m_customEventQueue);
    m_client.connect("localhost", 6612);
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        m_client.checkData();
        m_window.clear();
        m_currentScreen->handleEvent(event);

        CustomEvent customEvent;
        m_customEventQueue.pollEvent(customEvent);
        if (customEvent.type() != CustomEvent::None) {
            m_currentScreen->handleCustomEvent(customEvent);
        }

        m_currentScreen->draw();
        m_window.display();
    }

    return EXIT_SUCCESS;
}

void Game::setScreen(std::shared_ptr<Screen::Screen> screen) {
    m_currentScreen = screen;
}
