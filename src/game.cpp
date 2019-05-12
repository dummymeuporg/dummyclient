#include <cstdlib>

#include "custom_event_queue.hpp"
#include "game.hpp"
#include "screen/select_character_screen.hpp"
#include "resource_provider.hpp"
#include "widget_builder.hpp"

Game::Game(const char* account, const char* sessionID) 
    : m_client(Credentials(account, sessionID)),
      m_window(sf::VideoMode(1024, 768), "DummyClient")
{ }

int Game::run()
{
    ResourceProvider resourceProvider;
    CustomEventQueue customEventQueue;
    WidgetBuilder widgetBuilder(resourceProvider, customEventQueue);
    std::shared_ptr<Screen::SelectCharacterScreen> screen(
        new Screen::SelectCharacterScreen(*this, m_client, widgetBuilder)
    );
    m_client.setScreen(screen);
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
        m_client.screen()->handleEvent(event);

        CustomEvent customEvent;
        customEventQueue.pollEvent(customEvent);
        m_client.screen()->handleCustomEvent(customEvent);

        m_client.screen()->draw();
        m_window.display();
    }

    return EXIT_SUCCESS;
}
