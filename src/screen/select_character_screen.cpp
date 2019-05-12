#include <sstream>
#include <iostream>

#include "client.hpp"
#include "game.hpp"

#include "model/characters_list_model.hpp"
#include "screen/create_character_screen.hpp"
#include "screen/select_character_screen.hpp"

namespace Screen {

SelectCharacterScreen::SelectCharacterScreen(::Game& game,
                                             ::Client& client,
                                             ::WidgetBuilder& widgetBuilder)
    : UIScreen(game, client, widgetBuilder), m_charactersCount(-1),
      m_createCharacterButton(widgetBuilder.build<Widget::Button>()),
      m_accountLabel(widgetBuilder.build<Widget::Label>()),
    m_charactersCountLabel(widgetBuilder.build<Widget::Label>())
{
    m_createCharacterButton->setPos(850, 700);
    m_createCharacterButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(18);

    m_createCharacterButton->setFont("arial.ttf");
    m_createCharacterButton->setCaption("New character");

    std::cerr << "Account is " << m_client.account() << std::endl;
    m_accountLabel
        ->setCaption(m_client.account())
        .setFontSize(24)
        .setColor(sf::Color::Red)
        .setStyle(sf::Text::Bold | sf::Text::Underlined)
        .setFont("arial.ttf")
        .setPos(100, 100);

    m_charactersCountLabel
        ->setFontSize(24)
        .setColor(sf::Color::White)
        .setFont("arial.ttf");

    addWidget(m_accountLabel);
    addWidget(m_createCharacterButton);
    addWidget(m_charactersCountLabel);
}

void SelectCharacterScreen::notify() {
    const Model::CharactersListModel* model = 
        reinterpret_cast<const Model::CharactersListModel*>(m_model.get());
    std::cerr << "Screen notified. Update info." << std::endl;
    std::stringstream ss;
    m_charactersCount = model->characters().size();
    ss << "You have " << m_charactersCount << " characters";

    m_charactersCountLabel->setCaption(ss.str());

    // Center the label
    sf::Text& caption(m_charactersCountLabel->caption());
    sf::FloatRect textRect = caption.getLocalBounds();
    caption.setOrigin(textRect.left + textRect.width/2.0f,
                      textRect.top  + textRect.height/2.0f);
    caption.setPosition(1042/2, 768/2);
}

/*
void SelectCharacterScreen::draw() {
    UIScreen::draw();
    sf::RenderWindow& window(m_game.window());
    sf::Font& font(widgetBuilder().resourceProvider().font("arial.ttf"));
    sf::Text text;
    text.setFont(font);

    text.setString(m_client.account());

    text.setCharacterSize(24);

    text.setColor(sf::Color::Red);

    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text);
}
*/

void SelectCharacterScreen::handleCustomEvent(const ::CustomEvent& event)
{
    auto self(shared_from_this());
    if (event.source() == m_createCharacterButton.get()) {
        std::cerr << "Create character please." << std::endl;
        m_game.setScreen(std::make_shared<CreateCharacterScreen>(
            m_game, m_client, widgetBuilder()));
    }
}

} // namespace Screen
