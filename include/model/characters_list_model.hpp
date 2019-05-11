#pragma once

#include <vector>

#include "protocol/character_info.hpp"
#include "model/model.hpp"

using CharactersList = std::vector<Dummy::Protocol::CharacterInfo>;

namespace Model {

class CharactersListModel : public Model {
public:
    CharactersListModel();
    void addCharacter(Dummy::Protocol::CharacterInfo chacacterInfo);
    const CharactersList& characters() const {
        return m_characters;
    }
private:
    CharactersList m_characters;
};

} // namespace model
