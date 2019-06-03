#include "client.hpp"

#include "model/model.hpp"
#include "screen/screen.hpp"

namespace Screen {
Screen::Screen(::Game& game, ::Client& client)
    : m_game(game), m_client(client)
{
}

Screen::~Screen() {
    std::cerr << "screen destructor." << std::endl;
}

void Screen::loaded() {

}

void Screen::tick() {

}

} // namespace Screen
