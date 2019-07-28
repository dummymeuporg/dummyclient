#pragma once

#include <memory>

#include <dummy/core/character.hpp>

#include "graphics/living_state/state.hpp"
#include "graphics/entity.hpp"

class MapView;

namespace Graphics {

using Direction = Dummy::Core::Character::Direction;

class Living : public Entity {
public:
    Living(const MapView& mapView,
           const std::string& chipset,
           const std::string& name,
           std::size_t w,
           std::size_t h,
           std::int32_t x,
           std::int32_t y,
           std::uint8_t floor,
           std::size_t scaleFactor,
           Direction = Direction::DOWN,
           std::uint8_t velocity = 5);
    Living(const Living&);
    void draw(sf::RenderWindow&) override;
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

    std::uint8_t floor() const {
        return m_floor;
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

    void say(const std::string&);


protected:
    virtual void updatePosition();
    std::pair<std::int16_t, std::int16_t> computeDistance();
    void drawMessage(sf::RenderWindow&);

    std::string m_name;
    std::uint8_t m_floor;
    Direction m_direction;
    std::shared_ptr<LivingState::State> m_state;
    sf::Text m_displayName;
    std::uint8_t m_velocity;
    sf::Clock m_movingClock;
    int m_xMovement, m_yMovement;

    // XXX : This looks a bit cumbersome.
    bool m_isSpeaking;
    std::string m_messageToSay;
    sf::Clock m_messageToSayClock;
    sf::Text m_speech;
    sf::RectangleShape m_messageRect;

private:
    void _setDisplayName();
};

} // namespace Graphics
