#include <sstream>
#include <iostream>

#include "client.hpp"
#include "game.hpp"

#include "model/characters_list_model.hpp"
#include "screen/create_character_screen.hpp"
#include "screen/select_character_screen.hpp"

namespace Screen {

SelectCharacterScreen::SelectCharacterScreen(::Game& game,
                                             ::Client& client)
    : UIScreen(game, client), m_charactersCount(-1),
      m_createCharacterButton(std::make_shared<Widget::Button>()),
      m_playButton(std::make_shared<Widget::Button>()),
      m_accountLabel(std::make_shared<Widget::Label>()),
    m_charactersCountLabel(std::make_shared<Widget::Label>()),
    m_skinPreviewer(std::make_shared<Widget::SkinPreviewer>()),
    m_characterSelector(std::make_shared<Widget::CharacterSelector>())
{
    m_playButton->setPos(880, 730);
    m_playButton
        ->setBackgroundColor(sf::Color(183, 109, 44))
        .setBorderColor(sf::Color(94, 47, 6))
        .setColor(sf::Color::Black)
        .setStyle(0)
        .setFontSize(18);
    m_playButton->setFont("arial.ttf");
    m_playButton->setCaption("Play");

    m_createCharacterButton->setPos(950, 730);
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

    m_skinPreviewer->setPos(400, 400);

    // 322 = (1024/2) - (width of character selector / 2)
    m_characterSelector->setPos(322, 600);

    addWidget(m_accountLabel);
    addWidget(m_playButton);
    addWidget(m_createCharacterButton);
    addWidget(m_charactersCountLabel);
    addWidget(m_skinPreviewer);
    addWidget(m_characterSelector);
}

void SelectCharacterScreen::notify() {
    std::shared_ptr<Model::CharactersListModel> model = 
        std::dynamic_pointer_cast<Model::CharactersListModel>(m_model);
    std::stringstream ss;
    m_charactersCount = model->characters().size();
    ss << "You have " << m_charactersCount << " characters";

    m_charactersCountLabel->setCaption(ss.str());
    m_characterSelector->setCharacters(model->characters());

    // Center the label
    sf::Text& caption(m_charactersCountLabel->caption());
    sf::FloatRect textRect = caption.getLocalBounds();
    caption.setOrigin(textRect.left + textRect.width/2.0f,
                      textRect.top  + textRect.height/2.0f);
    caption.setPosition(1042/2, 768/2);
}

void SelectCharacterScreen::handleCustomEvent(const ::CustomEvent& event)
{
    auto self(shared_from_this());
    if (event.source() == m_createCharacterButton.get()) {
        std::cerr << "Create character please." << std::endl;
        std::shared_ptr<CreateCharacterScreen> screen =
            std::make_shared<CreateCharacterScreen>(m_game, m_client);
        screen->setModel(m_model);
        m_game.setScreen(screen);
    } else if (event.source() == m_characterSelector.get()) {
        std::shared_ptr<const Dummy::Core::Character> character =
            m_characterSelector->selectedCharacter();
        std::cerr << "Selected character: " <<
            m_characterSelector->selectedCharacter() << std::endl;
        m_skinPreviewer->setSkinList(
            std::vector<std::string>({character->skin()})
        );
    }
}

} // namespace Screen
