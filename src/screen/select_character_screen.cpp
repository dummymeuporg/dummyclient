#include <sstream>
#include <iostream>

#include "client.hpp"
#include "game.hpp"

#include "model/characters_list_model.hpp"
#include "screen/select_character_screen.hpp"

namespace Screen {

SelectCharacterScreen::SelectCharacterScreen(::Game& game,
                                             ::Client& client)
    : Screen(game, client), m_charactersCount(-1)
{
}

void SelectCharacterScreen::notify() {
    const Model::CharactersListModel* model = 
        reinterpret_cast<const Model::CharactersListModel*>(m_model.get());
    std::cerr << "Screen notified. Update info." << std::endl;
    m_charactersCount = model->characters().size();
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

    if (m_charactersCount >= 0) {
        std::stringstream ss;
        ss << "You have " << m_charactersCount << " characters.";
        sf::Text countText;
		countText.setString(ss.str());
        countText.setFont(m_game.font("arial.ttf"));
        countText.setCharacterSize(24);
        countText.setColor(sf::Color::White);
        sf::FloatRect textRect = countText.getLocalBounds();
		countText.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top  + textRect.height/2.0f);
		countText.setPosition(1042/2, 768/2);
        window.draw(countText);
	}
}

} // namespace Screen
