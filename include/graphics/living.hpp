#pragma once

#include <memory>

#include "core/character.hpp"

#include "graphics/living_state/state.hpp"
#include "graphics/entity.hpp"

namespace Graphics {

using Direction = Dummy::Core::Character::Direction;

class Living : public Entity {
public:
    Living(const std::string&,
           const std::string&,
           std::size_t,
           std::size_t,
           std::size_t,
           std::size_t,
           std::size_t,
           Direction = Direction::DOWN);
    Living(const Living&);
    virtual void draw(sf::RenderWindow&, const ::Camera&) override;
    const Dummy::Core::Character::Direction& direction() const {
        return m_direction;
    }

    Living& setPosition(std::uint16_t, std::uint16_t);
    Living& setDirection(Direction);
    Living& changeState(std::shared_ptr<LivingState::State>);
    sf::Text& displayName() {
        return m_displayName;
    }

    void moveTowards(std::uint16_t, std::uint16_t);
protected:
    std::string m_name;
    Direction m_direction;
    std::shared_ptr<LivingState::State> m_state;
    sf::Text m_displayName;

private:
    void _setDisplayName();
};

} // namespace Graphics
