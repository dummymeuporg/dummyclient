#include "client.hpp"

#include "game.hpp"
#include "screen/screen.hpp"

namespace Screen {
Screen::Screen(::Game& game, ::Client& client)
    : m_game(game), m_client(client),
      m_resourceProvider(m_game.resourceProvider())
{
}

Screen::~Screen() {
    std::cerr << "screen destructor." << std::endl;
}

void Screen::loaded() {

}

void Screen::tick() {

}

void Screen::returned() {
    focusChild(nullptr);
    resetHovering();
}

sf::IntRect Screen::boundingRect() const {
    return sf::IntRect(
        0,
        0,
        static_cast<int>(m_game.width()),
        static_cast<int>(m_game.height())
    );
}

} // namespace Screen
