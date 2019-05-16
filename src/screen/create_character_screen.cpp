#include "client.hpp"
#include "game.hpp"
#include "screen/create_character_screen.hpp"
#include "widget/label.hpp"

namespace Screen {

CreateCharacterScreen::CreateCharacterScreen(::Game& game,
                                             ::Client& client,
                                             ::WidgetBuilder& widgetBuilder)
    : UIScreen(game, client, widgetBuilder),
      m_characterNameLabel(widgetBuilder.build<Widget::Label>()),
      m_characterNameTextbox(widgetBuilder.build<Widget::Textbox>()),
      m_characterSkinLabel(widgetBuilder.build<Widget::Label>()),
      m_skinPicker(std::make_shared<Widget::SkinPicker>(
          std::vector<std::string>({"WhiteScale.png"})
      ))
{
    m_characterNameLabel
        ->setCaption("Name: ")
        .setFontSize(24)
        .setColor(sf::Color::White)
        .setStyle(sf::Text::Bold)
        .setFont("arial.ttf")
        .setPos(100, 100);

    m_characterNameTextbox
        ->setFontSize(24)
        .setColor(sf::Color::Black)
        .setBackgroundColor(sf::Color(200, 200, 200))
        .setBorderColor(sf::Color(128, 128, 128))
        .setRect(230, 90, 200, 40)
        .setContent("Name")
        .setFont("arial.ttf");

    m_characterSkinLabel
        ->setCaption("Skin: ")
        .setFontSize(24)
        .setColor(sf::Color::White)
        .setStyle(sf::Text::Bold)
        .setFont("arial.ttf")
        .setPos(100, 200);

    m_skinPicker
        ->setPos(230, 200);

    addWidget(m_characterNameLabel);
    addWidget(m_characterNameTextbox);
    addWidget(m_characterSkinLabel);
    addWidget(m_skinPicker);
}

} // namespace Screen
