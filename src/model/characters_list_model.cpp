#include <iostream>
#include <memory>

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
    update();
}

}
