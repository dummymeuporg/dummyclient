#include <iostream>
#include "camera.hpp"
#include "graphics/living.hpp"
#include "graphics/living_state/standing_state.hpp"
#include "graphics/living_state/walking_state.hpp"

namespace Graphics {
namespace LivingState {

StandingState::StandingState(Graphics::Living& living) :
    State(living)
{
}

void StandingState::draw(sf::RenderWindow& window) {
    const sf::Vector2u& windowSize(window.getSize());
    sf::Sprite& sprite(m_living.sprite());
    sprite.setTextureRect(sf::IntRect(
        m_living.w(),
        m_living.h() * static_cast<std::uint8_t>(m_living.direction()),
        m_living.w(),
        m_living.h()
    ));

    int xPos = m_living.x();
    int yPos = m_living.y();
    sprite.setPosition(xPos, yPos);
    window.draw(sprite);
}

void StandingState::moveTowards(std::uint16_t x, std::uint16_t y) {
    auto self(shared_from_this());
    if (m_living.x() != x || m_living.y() != y) {
        m_living.changeState(
            std::make_shared<LivingState::WalkingState>(m_living)
        );
        if (m_living.yMovement() > 0) {
            m_living.setDirection(Dummy::Core::Character::Direction::DOWN);
        } else if(m_living.yMovement() < 0) {
            m_living.setDirection(Dummy::Core::Character::Direction::UP);
        } else if (m_living.xMovement() > 0) {
            m_living.setDirection(Dummy::Core::Character::Direction::RIGHT);
        } else if (m_living.xMovement() < 0) {
            m_living.setDirection(Dummy::Core::Character::Direction::LEFT);
        }

    }
}

void StandingState::walk() {
    auto self(shared_from_this());
    m_living.changeState(
        std::make_shared<LivingState::WalkingState>(m_living)
    );
}

void StandingState::stand() {
    // Do nothing; already standing.
}

} // namespace LivingState
} // namespace Graphics
