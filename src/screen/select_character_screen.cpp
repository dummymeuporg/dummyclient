#include <sstream>
#include <iostream>

#include "client.hpp"
#include "game.hpp"

#include "model/characters_list_model.hpp"
#include "screen/select_character_screen.hpp"

namespace Screen {

SelectCharacterScreen::SelectCharacterScreen(::Game& game,
                                             ::Client& client,
                                             ::WidgetBuilder& widgetBuilder)
    : UIScreen(game, client, widgetBuilder), m_charactersCount(-1)
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
    sf::Font& font(widgetBuilder().resourceProvider().font("arial.ttf"));
    sf::Text text;
    text.setFont(font);

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
        countText.setFont(font);
        countText.setCharacterSize(24);
        countText.setColor(sf::Color::White);
        sf::FloatRect textRect = countText.getLocalBounds();
		countText.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top  + textRect.height/2.0f);
		countText.setPosition(1042/2, 768/2);
        window.draw(countText);
	}
}

void SelectCharacterScreen::handleEvent(const sf::Event& event) {

}

} // namespace Screen
