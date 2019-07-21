#pragma once

#include <memory>

#include "core/character.hpp"

#include "graphics/living_state/state.hpp"
#include "graphics/entity.hpp"

class MapView;

namespace Graphics {

using Direction = Dummy::Core::Character::Direction;

class Living : public Entity {
public:
    Living(const MapView&,
           const std::string&,
           const std::string&,
           std::size_t,
           std::size_t,
           std::size_t,
           std::size_t,
           std::size_t,
           Direction = Direction::DOWN,
           std::uint8_t velocity = 5);
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
    virtual void tick();

    std::uint8_t velocity() const {
        return m_velocity;
    }

    void setVelocity(std::uint8_t);

    int xMovement() const {
        return m_xMovement;
    }

    int yMovement() const {
        return m_yMovement;
    }

    void setXMovement(int);
    void setYMovement(int);

    void walk();
    void stand();

protected:
    virtual void updatePosition();
    std::pair<std::int16_t, std::int16_t> computeDistance();

    std::string m_name;
    Direction m_direction;
    std::shared_ptr<LivingState::State> m_state;
    sf::Text m_displayName;
    std::uint8_t m_velocity;
    sf::Clock m_movingClock;
    int m_xMovement, m_yMovement;

private:
    void _setDisplayName();
};

} // namespace Graphics
