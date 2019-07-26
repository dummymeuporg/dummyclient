#include <sstream>
#include <iostream>

#include "client.hpp"
#include "game.hpp"

#include <dummy/server/command/connect_command.hpp>
#include <dummy/server/command/get_primary_info_command.hpp>
#include <dummy/server/command/select_character.hpp>
#include <dummy/server/response/connect_response.hpp>
#include <dummy/server/response/characters_list_response.hpp>
#include <dummy/server/response/select_character.hpp>

#include <dummy/protocol/outgoing_packet.hpp>

#include "screen/create_character_screen.hpp"
#include "screen/loading_screen.hpp"
#include "screen/select_character_screen.hpp"

namespace Screen {

SelectCharacterScreen::SelectCharacterScreen(::Game& game,
                                             ::Client& client)
    : UIScreen(game, client),
      m_selectedCharacter(nullptr),
      m_createCharacterButton(std::make_shared<Widget::Button>()),
      m_playButton(std::make_shared<Widget::Button>()),
      m_accountLabel(std::make_shared<Widget::Label>()),
    m_charactersCountLabel(std::make_shared<Widget::Label>()),
    m_skinPreviewer(std::make_shared<Widget::SkinPreviewer>()),
    m_characterSelector(std::make_shared<Widget::CharacterSelector>())
{
    m_playButton->setPos(300, 200);
    m_playButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(18);
    m_playButton->setFont("arial.ttf");
    m_playButton->setCaption("Play");
    m_playButton->setEnabled(false);

    m_createCharacterButton->setPos(500, 500);
    m_createCharacterButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(18);
    m_createCharacterButton->setFont("arial.ttf");
    m_createCharacterButton->setCaption("Create");

    m_accountLabel
        ->setCaption(m_client.account())
        .setFontSize(24)
        .setColor(sf::Color::Red)
        .setStyle(sf::Text::Bold | sf::Text::Underlined)
        .setFont("arial.ttf")
        .setPos(0, 0);

    m_charactersCountLabel
        ->setFontSize(24)
        .setColor(sf::Color::White)
        .setFont("arial.ttf");

    // 448 = (width/2) - (24*4)
    m_skinPreviewer->setPos(384, 120);

    // 450 = (width/2) - (width of character selector (380) / 2)
    m_characterSelector->setPos(310, 600);

    addWidget(m_accountLabel);
    addWidget(m_playButton);
    addWidget(m_createCharacterButton);
    addWidget(m_charactersCountLabel);
    addWidget(m_skinPreviewer);
    addWidget(m_characterSelector);
}

SelectCharacterScreen::~SelectCharacterScreen()
{}

void SelectCharacterScreen::loaded() {
    std::cerr << "Send command for primary info" << std::endl;
    Dummy::Server::Command::ConnectCommand cmd(
        m_client.credentials().account(),
        m_client.credentials().sessionID()
    );
    m_client.sendCommand(cmd);
}


void SelectCharacterScreen::returned() {
    _refreshCharactersList();
}

void SelectCharacterScreen::handleCustomEvent(const ::CustomEvent& event)
{
    auto self(shared_from_this());
    if (event.source() == m_createCharacterButton.get()) {
        std::cerr << "Create character please." << std::endl;
        std::shared_ptr<CreateCharacterScreen> screen =
            std::make_shared<CreateCharacterScreen>(
                m_game,
                m_client,
                m_characters
            );
        m_client.setScreen(screen, true);
    } else if (event.source() == m_characterSelector.get()) {
        std::shared_ptr<const Dummy::Core::Character> character =
            m_characterSelector->selectedCharacter();
        std::cerr << "Selected character: " <<
            m_characterSelector->selectedCharacter() << std::endl;
        m_skinPreviewer->setSkinList(
            std::vector<std::string>({character->skin()})
        );
        m_playButton->setEnabled(true);
    } else if (event.source() == m_playButton.get()) {
        m_selectedCharacter = 
            m_characterSelector->selectedCharacter();

        Dummy::Server::Command::SelectCharacter selectCharacter(
            m_selectedCharacter->name()
        );

        m_client.sendCommand(selectCharacter);
    }
}

void SelectCharacterScreen::onResponse(
    const Dummy::Server::Response::Response& response
) {
    response.accept(*this);
}

void SelectCharacterScreen::visitResponse(
    const Dummy::Server::Response::ConnectResponse& response
) {
    std::cerr << "Got connect response." << std::endl;
    switch(response.status()) {
    case 0: /* O.K. */
        m_client.sendCommand(Dummy::Server::Command::GetPrimaryInfoCommand());
        break;
    default: /* Quit the program */
        // XXX: Find a neater way to quit.
        ::exit(-1);
        break;
    }
}

void SelectCharacterScreen::_refreshCharactersList() {
    std::cerr << "Got characters list." << std::endl;
    std::stringstream ss;
    ss << "You have " << m_characters.size() << " characters";

    m_charactersCountLabel->setCaption(ss.str());
    m_characterSelector->setCharacters(m_characters);

    // Center the label
    sf::Text& caption(m_charactersCountLabel->caption());
    sf::FloatRect textRect = caption.getLocalBounds();
    caption.setOrigin(textRect.left + textRect.width/2.0f,
                      textRect.top  + textRect.height/2.0f);
    caption.setPosition(m_game.width()/2, m_game.height()/2);
}

void SelectCharacterScreen::visitResponse(
    const Dummy::Server::Response::CharactersListResponse& response
) {
    m_characters = std::move(response.charactersList());
    _refreshCharactersList();
}


void SelectCharacterScreen::visitResponse(
    const Dummy::Server::Response::SelectCharacter&
) {

    auto self(shared_from_this());
    std::shared_ptr<LoadingScreen> screen = std::make_shared<LoadingScreen>(
        m_game, m_client, m_selectedCharacter->mapLocation(), "main"
    );
    m_client.setCharacter(m_selectedCharacter);
    m_client.setScreen(screen, true);

}

} // namespace Screen
