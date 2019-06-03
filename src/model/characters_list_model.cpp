#include <iostream>
#include <memory>

#include "screen/create_character_screen.hpp"
#include "screen/select_character_screen.hpp"
#include "model/characters_list_model.hpp"

namespace Model {

CharactersListModel::CharactersListModel() {
    std::cerr << this << " CharactersListModel constructor." << std::endl;
}

CharactersListModel::~CharactersListModel() {
    std::cerr << this << " CharactersListModel destructor." << std::endl;
}

void
CharactersListModel::addCharacter(
    std::shared_ptr<Dummy::Core::Character> character
)
{
    std::cerr << "Add character." << std::endl;
    std::cerr << character->name() << std::endl;
    std::cerr << character->skin() << std::endl;
    std::cerr << character->position().first << std::endl;
    std::cerr << character->position().second << std::endl;
    std::cerr << character->mapLocation() << std::endl;

    m_characters.push_back(character);
    std::cerr << "New size: " << m_characters.size() << std::endl;
}


void
CharactersListModel::visit(
    std::shared_ptr<Screen::SelectCharacterScreen> screen
) {
    screen->setCharacters(m_characters);
}

void
CharactersListModel::visit(
    std::shared_ptr<Screen::CreateCharacterScreen> screen
)
{
    if (screen->initialCharactersCount() < m_characters.size()) {
        // There is a new character so the creation succeeded.
        pushEvent(
            ::CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::CharacterCreated,
                reinterpret_cast<void*>(screen.get())
            )
        );
    }

}

}
