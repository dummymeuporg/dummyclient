#pragma once

#include <vector>

#include "core/character.hpp"
#include "model/model.hpp"


namespace Model {

class CharactersListModel : public Model {
public:
    using CharactersList =
        std::vector<std::shared_ptr<Dummy::Core::Character>>;
    CharactersListModel();
    void addCharacter(std::shared_ptr<Dummy::Core::Character>);
    const CharactersList& characters() const {
        return m_characters;
    }
private:
    CharactersList m_characters;
};

} // namespace model
