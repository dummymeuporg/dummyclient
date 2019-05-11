#include "client.hpp"
#include "game.hpp"

#include "screen/select_character_screen.hpp"

namespace Screen {

SelectCharacterScreen::SelectCharacterScreen(::Game& game,
                                             ::Client& client)
    : Screen(game, client)
{
}

void SelectCharacterScreen::notify() {
}

void SelectCharacterScreen::draw() {
    sf::RenderWindow& window(m_game.window());
    sf::Text text;
    text.setFont(m_game.font("arial.ttf"));

    text.setString(m_client.account());

    text.setCharacterSize(24);

    text.setColor(sf::Color::Red);

    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text);

}

} // namespace Screen
