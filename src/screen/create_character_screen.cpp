#include <iostream>
#include "client.hpp"
#include "game.hpp"
#include "model/characters_list_model.hpp"
#include "screen/create_character_screen.hpp"
#include "screen/select_character_screen.hpp"
#include "widget/label.hpp"

namespace Screen {

CreateCharacterScreen::CreateCharacterScreen(::Game& game,
                                             ::Client& client)
    : UIScreen(game, client),
      m_initialCharactersCount(0),
      m_characterNameLabel(std::make_shared<Widget::Label>()),
      m_characterNameTextbox(std::make_shared<Widget::Textbox>()),
      m_characterSkinLabel(std::make_shared<Widget::Label>()),
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
      m_rightSkinButton(std::make_shared<Widget::Button>()),
      m_createCharacterButton(std::make_shared<Widget::Button>()),
      m_cancelButton(std::make_shared<Widget::Button>())
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
        .setRect(230, 90, 420, 40)
        .setMaxLength(25)
        .setContent("")
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

    m_createCharacterButton->setPos(220, 450);
    m_createCharacterButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(24);
    m_createCharacterButton->setFont("arial.ttf");
    m_createCharacterButton->setCaption("Create");

    m_cancelButton->setPos(900, 600);
    m_cancelButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(24);
    m_cancelButton->setFont("arial.ttf");
    m_cancelButton->setCaption("Cancel");

    addWidget(m_characterNameLabel);
    addWidget(m_characterNameTextbox);
    addWidget(m_characterSkinLabel);
    addWidget(m_skinPreviewer);
    addWidget(m_leftSkinButton);
    addWidget(m_rightSkinButton);
    addWidget(m_createCharacterButton);
    addWidget(m_cancelButton);
}

void CreateCharacterScreen::_handleButtonClicked(const ::CustomEvent& event) {
    if (event.source() == m_leftSkinButton.get()) {
        m_skinPreviewer->showPreviousSkin();
    } else if(event.source() == m_rightSkinButton.get()) {
        m_skinPreviewer->showNextSkin();
    } else if (event.source() == m_createCharacterButton.get()) {
        _onCreateCharacterButton();
    } else if (event.source() == m_cancelButton.get()) {
        _back();
    }
}

void CreateCharacterScreen::_onCreateCharacterButton() {
    // Memorize the characters count from model first.
    const Model::CharactersListModel* model = 
        reinterpret_cast<const Model::CharactersListModel*>(m_model.get());
    m_initialCharactersCount = model->characters().size();
    const std::string& characterName(m_characterNameTextbox->content());
    const std::string& skin(m_skinPreviewer->skin());
    std::cerr << "Name: " << m_characterNameTextbox->content()
        << std::endl;
    std::cerr << "Chipset: " << m_skinPreviewer->skin()
        << std::endl;

    Dummy::Protocol::OutgoingPacket pkt;
    std::uint8_t command = 1; // create_character

    pkt << command << characterName << skin;
    m_client.send(pkt);

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

void CreateCharacterScreen::_back() {
    auto self(shared_from_this());
    std::shared_ptr<SelectCharacterScreen> screen =
        std::make_shared<SelectCharacterScreen>(m_game, m_client);
    screen->setModel(m_model);
    m_game.setScreen(screen);
}

void CreateCharacterScreen::notify() {
    // Get the characters count from model
    const Model::CharactersListModel* model = 
        reinterpret_cast<const Model::CharactersListModel*>(m_model.get());
    int charactersCount = model->characters().size();

    if (m_initialCharactersCount < charactersCount) {
        // There is a new character so the creation succeeded.
        _back();
    }
}

} // namespace Screen
