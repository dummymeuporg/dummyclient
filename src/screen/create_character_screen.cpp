#include "client.hpp"
#include "game.hpp"
#include "screen/create_character_screen.hpp"
#include "widget/label.hpp"

namespace Screen {

CreateCharacterScreen::CreateCharacterScreen(::Game& game,
                                             ::Client& client,
                                             ::WidgetBuilder& widgetBuilder)
    : UIScreen(game, client, widgetBuilder),
      m_characterNameLabel(widgetBuilder.build<Widget::Label>())
{
    m_characterNameLabel
        ->setCaption("Name: ")
        .setFontSize(24)
        .setColor(sf::Color::White)
        .setStyle(sf::Text::Bold)
        .setFont("arial.ttf")
        .setPos(100, 100);

    addWidget(m_characterNameLabel);
}

} // namespace Screen
