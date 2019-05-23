#pragma once

#include <vector>

#include "core/character.hpp"
#include "model/model.hpp"

using CharactersList = std::vector<Dummy::Core::Character>;

namespace Model {

class CharactersListModel : public Model {
public:
    CharactersListModel();
    void addCharacter(Dummy::Core::Character&& chacacterInfo);
    const CharactersList& characters() const {
        return m_characters;
    }
private:
    CharactersList m_characters;
};

} // namespace model
