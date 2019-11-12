#include <iostream>

#include <dummy/core/character.hpp>
#include <dummy/server/errors.hpp>
#include <dummy/server/command/create_character.hpp>
#include <dummy/server/response/create_character.hpp>

#include "client.hpp"
#include "game.hpp"
#include "screen/create_character_screen.hpp"
#include "screen/select_character_screen.hpp"
#include "widget/label.hpp"


using CreateCharacterStatus = Dummy::Server::CreateCharacterError::Code;

namespace Screen {

CreateCharacterScreen::CreateCharacterScreen(
    ::Game& game, ::Client& client,
    std::vector<std::shared_ptr<Dummy::Core::Character>>& characters
    )
    : UIScreen(game, client),
      m_selectedCharacterClass(Dummy::Core::Character::Class::NONE),
      m_characters(characters),
      m_characterNameLabel(std::make_shared<Widget::Label>(*this)),
      m_characterNameTextbox(std::make_shared<Widget::Textbox>(*this)),
      m_characterSkinLabel(std::make_shared<Widget::Label>(*this)),
      m_skinPreviewer(std::make_shared<Widget::SkinPreviewer>(
          *this,
          std::vector<std::string>({"Avanta.png",
                                    "bluewarrior.png",
                                    "Cyana.png",
                                    "Lily-csl.png",
                                    "Quelqun-tiny.png",
                                    "tykelj2.png",
                                    "WhiteScale.png",
                                    "WhiteScale2.png"})
      )),
      m_leftSkinButton(std::make_shared<Widget::Button>(*this)),
      m_rightSkinButton(std::make_shared<Widget::Button>(*this)),
      m_createCharacterButton(std::make_shared<Widget::Button>(*this)),
      m_cancelButton(std::make_shared<Widget::Button>(*this)),
      m_characterClassLabel(std::make_shared<Widget::Label>(*this)),
      m_characterClassValue(std::make_shared<Widget::Label>(*this)),
      m_chooseGrognardButton(std::make_shared<Widget::Button>(*this)),
      m_chooseSentinelleButton(std::make_shared<Widget::Button>(*this)),
      m_chooseSpadassinButton(std::make_shared<Widget::Button>(*this))
{
    m_characterNameLabel
        ->setCaption("Name: ")
        .setFontSize(18)
        .setColor(sf::Color::White)
        .setStyle(sf::Text::Bold)
        .setFont("arial.ttf")
        .setPos(100, 100);

    m_characterNameTextbox
        ->setFontSize(18)
        .setColor(sf::Color::Black)
        .setBackgroundColor(sf::Color(200, 200, 200))
        .setBorderColor(sf::Color(128, 128, 128))
        .setRect(230, 90, 420, 40)
        .setMaxLength(25)
        .setContent("")
        .setFont("arial.ttf");

    m_characterSkinLabel
        ->setCaption("Skin: ")
        .setFontSize(18)
        .setColor(sf::Color::White)
        .setStyle(sf::Text::Bold)
        .setFont("arial.ttf")
        .setPos(100, 200);

    m_leftSkinButton->setPos(220, 220);
    m_leftSkinButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(36);
    m_leftSkinButton->setFont("arial.ttf");
    m_leftSkinButton->setCaption("<");

    m_skinPreviewer->setPos(260, 180);

    m_rightSkinButton->setPos(400, 220);
    m_rightSkinButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(36);
    m_rightSkinButton->setFont("arial.ttf");
    m_rightSkinButton->setCaption(">");

    m_createCharacterButton->setPos(650, 600);
    m_createCharacterButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(18);
    m_createCharacterButton->setFont("arial.ttf");
    m_createCharacterButton->setCaption("Create");

    m_cancelButton->setPos(800, 600);
    m_cancelButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(18);
    m_cancelButton->setFont("arial.ttf");
    m_cancelButton->setCaption("Cancel");

    m_characterClassLabel->setPos(100, 320);
    m_characterClassLabel->setCaption("Class: ");
    m_characterClassLabel->setFontSize(18);
    m_characterClassLabel->setColor(sf::Color::White);
    m_characterClassLabel->setStyle(sf::Text::Bold);
    m_characterClassLabel->setFont("arial.ttf");

    m_characterClassValue->setPos(250, 320);
    m_characterClassValue->setCaption("");
    m_characterClassValue->setFontSize(18);
    m_characterClassValue->setColor(sf::Color::White);
    m_characterClassValue->setStyle(sf::Text::Bold);
    m_characterClassValue->setFont("arial.ttf");

    m_chooseGrognardButton->setPos(200, 400);
    m_chooseGrognardButton->setBackgroundColor(sf::Color(183, 109, 44));
    m_chooseGrognardButton->setBorderColor(sf::Color(94, 47, 6));
    m_chooseGrognardButton->setColor(sf::Color::Black);
    m_chooseGrognardButton->setStyle(0);
    m_chooseGrognardButton->setFontSize(18);
    m_chooseGrognardButton->setFont("arial.ttf");
    m_chooseGrognardButton->setCaption("Grognard");

    m_chooseSentinelleButton->setPos(320, 400);
    m_chooseSentinelleButton->setBackgroundColor(sf::Color(183, 109, 44));
    m_chooseSentinelleButton->setBorderColor(sf::Color(94, 47, 6));
    m_chooseSentinelleButton->setColor(sf::Color::Black);
    m_chooseSentinelleButton->setStyle(0);
    m_chooseSentinelleButton->setFontSize(18);
    m_chooseSentinelleButton->setFont("arial.ttf");
    m_chooseSentinelleButton->setCaption("Sentinelle");

    m_chooseSpadassinButton->setPos(440, 400);
    m_chooseSpadassinButton->setBackgroundColor(sf::Color(183, 109, 44));
    m_chooseSpadassinButton->setBorderColor(sf::Color(94, 47, 6));
    m_chooseSpadassinButton->setColor(sf::Color::Black);
    m_chooseSpadassinButton->setStyle(0);
    m_chooseSpadassinButton->setFontSize(18);
    m_chooseSpadassinButton->setFont("arial.ttf");
    m_chooseSpadassinButton->setCaption("Spadassin");


    addWidget(m_characterNameLabel);
    addWidget(m_characterNameTextbox);
    addWidget(m_characterSkinLabel);
    addWidget(m_skinPreviewer);
    addWidget(m_leftSkinButton);
    addWidget(m_rightSkinButton);
    addWidget(m_createCharacterButton);
    addWidget(m_cancelButton);
}

CreateCharacterScreen::~CreateCharacterScreen() { }

void CreateCharacterScreen::handleButtonClicked(const ::CustomEvent& event) {
    if (event.target() == m_leftSkinButton.get()) {
        m_skinPreviewer->showPreviousSkin();
    } else if(event.target() == m_rightSkinButton.get()) {
        m_skinPreviewer->showNextSkin();
    } else if (event.target() == m_createCharacterButton.get()) {
        if (m_selectedCharacterClass != Dummy::Core::Character::Class::NONE) {
            onCreateCharacterButton();
        }
    } else if (event.target() == m_cancelButton.get()) {
        back();
    } else if (event.target() == m_chooseGrognardButton.get()) {
        m_characterClassValue->setCaption("Grognard");
        m_selectedCharacterClass = Dummy::Core::Character::Class::GROGNARD;
    } else if (event.target() == m_chooseSpadassinButton.get()) {
        m_characterClassValue->setCaption("Spadassin");
        m_selectedCharacterClass = Dummy::Core::Character::Class::SPADASSIN;
    } else if (event.target() == m_chooseSentinelleButton.get()) {
        m_characterClassValue->setCaption("Sentinelle");
        m_selectedCharacterClass = Dummy::Core::Character::Class::SENTINELLE;
    }
}

void CreateCharacterScreen::onCreateCharacterButton() {
    const std::string& characterName(m_characterNameTextbox->content());
    const std::string& skin(m_skinPreviewer->skin());
    std::cerr << "Name: " << m_characterNameTextbox->content()
        << std::endl;
    std::cerr << "Chipset: " << m_skinPreviewer->skin()
        << std::endl;

    m_client.sendCommand(
        std::make_unique<Dummy::Server::Command::CreateCharacter>(
            characterName, skin, m_selectedCharacterClass
        )
    );
}

bool CreateCharacterScreen::handleCustomEvent(const ::CustomEvent& event) {
    switch(event.type()) {
    case CustomEvent::Type::LeftClick:
        handleButtonClicked(event);
        return false;
    case ::CustomEvent::Type::CharacterCreated:
        back();
        return false;
    default:
        return UIScreen::handleCustomEvent(event);
    }
}

void CreateCharacterScreen::back() {
    auto self(shared_from_this());
    m_client.returnToPreviousScreen();
}


void CreateCharacterScreen::onResponse(
    const Dummy::Server::Response::Response& response
) {
    response.accept(*this);
}


void CreateCharacterScreen::visitResponse(
    const Dummy::Server::Response::CreateCharacter& createCharacter
) {
    switch (createCharacter.status()) {
    case CreateCharacterStatus::OK:
        m_characters.push_back(createCharacter.character());
        pushEvent(
            ::CustomEvent(
                this,
                CustomEvent::CharacterCreated,
                this
            )
        );
        break;

    case CreateCharacterStatus::NAME_EMPTY:
        // XXX: print error
        break;

    // XXX: handle other errors.
    }

}

} // namespace Screen
