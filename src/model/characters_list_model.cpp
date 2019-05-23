#include <memory>

#include "model/characters_list_model.hpp"

namespace Model {

CharactersListModel::CharactersListModel() {}

void
CharactersListModel::addCharacter(Dummy::Core::Character&& characterInfo)
{
    m_characters.push_back(std::move(characterInfo));
}

}
