#include "screen/loading_screen.hpp"

namespace Screen {

LoadingScreen::LoadingScreen(::Game& game, ::Client& client)
    : UIScreen(game, client),
      m_label(std::make_shared<Widget::Label>())
{
    m_label
        ->setCaption("Loading...")
        .setFontSize(50)
        .setColor(sf::Color::White)
        .setStyle(sf::Text::Bold)
        .setFont("arial.ttf");

    sf::Text& caption(m_label->caption());
    sf::FloatRect textRect = caption.getLocalBounds();
    caption.setOrigin(textRect.left + textRect.width/2.0f,
                      textRect.top + textRect.height/2.0f);
    caption.setPosition(1024/2, 768/2);

    addWidget(m_label);
}

void LoadingScreen::notify() {

}

void LoadingScreen::handleCustomEvent(const ::CustomEvent& event)
{
}

} // namespace Screen
