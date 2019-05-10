#include "client.hpp"

#include "screen/select_character_screen.hpp"

namespace Screen {

SelectCharacterScreen::SelectCharacterScreen(sf::RenderWindow& window,
                                             ::Client& client)
    : Screen(window, client)
{
    if (!m_arialFont.loadFromFile("arial.ttf"))
    {
        // erreur...
    }

}

void SelectCharacterScreen::notify() {
}

void SelectCharacterScreen::draw() {
    sf::Text text;
    text.setFont(m_arialFont);

    text.setString(m_client.account());

    text.setCharacterSize(24);

    text.setColor(sf::Color::Red);

    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    m_window.draw(text);

}

} // namespace Screen
