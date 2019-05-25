#include <cstdlib>

#include "custom_event_queue.hpp"
#include "game.hpp"
#include "screen/create_character_screen.hpp"
#include "screen/select_character_screen.hpp"
#include "resource_provider.hpp"

Game::Game(const char* account, const char* sessionID) 
    : m_client(*this, Credentials(account, sessionID)),
      m_window(sf::VideoMode(1024, 768), "DummyClient"),
      m_customEventQueue(CustomEventQueue::instance()),
      m_resourceProvider(ResourceProvider::instance()),
      m_currentScreen(std::make_shared<Screen::SelectCharacterScreen>(
        *this, m_client))
{ }

int Game::run()
{
    m_client.connect("127.0.0.1", 6612);
    sf::Clock clock;
    m_window.setKeyRepeatEnabled(false);
    m_window.setFramerateLimit(Game::FPS);
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

        if (clock.getElapsedTime().asMilliseconds() > 1000/Game::FPS) {
            m_currentScreen->draw();
            m_window.display();
            clock.restart();
        }
        sf::sleep(sf::milliseconds(1));
    }

    return EXIT_SUCCESS;
}

void Game::setScreen(std::shared_ptr<Screen::Screen> screen) {
    std::cerr << "Change screen." << std::endl;
    m_currentScreen->detachFromModel();
    m_currentScreen = screen;
}
