#include <iostream>
#include <memory>

#include "model/characters_list_model.hpp"

namespace Model {

CharactersListModel::CharactersListModel() {}

void
CharactersListModel::addCharacter(Dummy::Core::Character&& character)
{
    std::cerr << character.name() << std::endl;
    std::cerr << character.skin() << std::endl;
    std::cerr << character.position().first << std::endl;
    std::cerr << character.position().second << std::endl;
    std::cerr << character.mapLocation() << std::endl;

    m_characters.push_back(std::move(character));
}

}
