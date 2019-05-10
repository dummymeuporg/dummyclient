#include "client.hpp"

#include "screen/screen.hpp"

namespace Screen {
Screen::Screen(sf::RenderWindow& window, ::Client& client)
    : m_window(window), m_client(client)
{
}

} // namespace Screen
