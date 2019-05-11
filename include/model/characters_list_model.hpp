#pragma once

#include <vector>

#include "protocol/character_info.hpp"
#include "model/model.hpp"

namespace Model {

class CharactersListModel : public Model {
public:
    CharactersListModel();
    void addCharacter(Dummy::Protocol::CharacterInfo chacacterInfo);
private:
    std::vector<Dummy::Protocol::CharacterInfo> m_characters;
};

} // namespace model
