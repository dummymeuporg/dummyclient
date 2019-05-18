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
      m_skinPreviewer(std::make_shared<Widget::SkinPreviewer>(
          std::vector<std::string>({"Avanta.png",
                                    "bluewarrior.png",
                                    "Cyana.png",
                                    "Lily-csl.png",
                                    "Quelqun-tiny.png",
                                    "tykelj2.png",
                                    "WhiteScale.png",
                                    "WhiteScale2.png"})
      )),
      m_leftSkinButton(std::make_shared<Widget::Button>()),
      m_rightSkinButton(std::make_shared<Widget::Button>())
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

    m_skinPreviewer->setPos(230, 200);

    m_leftSkinButton->setPos(220, 250);
    m_leftSkinButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(36);
    m_leftSkinButton->setFont("arial.ttf");
    m_leftSkinButton->setCaption("<");

    m_rightSkinButton->setPos(450, 250);
    m_rightSkinButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(36);
    m_rightSkinButton->setFont("arial.ttf");
    m_rightSkinButton->setCaption(">");

    addWidget(m_characterNameLabel);
    addWidget(m_characterNameTextbox);
    addWidget(m_characterSkinLabel);
    addWidget(m_skinPreviewer);
    addWidget(m_leftSkinButton);
    addWidget(m_rightSkinButton);
}

void CreateCharacterScreen::_handleButtonClicked(const ::CustomEvent& event) {
    if (event.source() == m_leftSkinButton.get()) {
        m_skinPreviewer->showPreviousSkin();
    } else if(event.source() == m_rightSkinButton.get()) {
        m_skinPreviewer->showNextSkin();
    }
}

void CreateCharacterScreen::handleCustomEvent(const ::CustomEvent& event) {
    switch(event.type()) {
    case ::CustomEvent::Type::ButtonClicked:
        _handleButtonClicked(event);
        break;
    default:
        UIScreen::handleCustomEvent(event);
        break;
    }
}

} // namespace Screen
