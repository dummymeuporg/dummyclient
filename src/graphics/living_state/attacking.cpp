#include <iostream>
#include "graphics/living.hpp"
#include "graphics/living_state/attacking.hpp"
#include "graphics/living_state/walking_state.hpp"
#include "graphics/living_state/standing_state.hpp"

namespace Graphics {
namespace LivingState {

Attacking::Attacking(Graphics::Living& living, int refreshFrame) :
    State(living), m_currentFrame(0), m_refreshFrame(refreshFrame)
{
    m_clock.restart();
}

void Attacking::draw(sf::RenderWindow& window) {
    auto self(shared_from_this());
    static const int FRAMES[] = {0, 1, 2};
    if (m_clock.getElapsedTime().asMilliseconds() >= m_refreshFrame/3) {
        ++m_currentFrame;
        if (m_currentFrame >= 3) {
            m_currentFrame = 0;
            stand();
        }
        m_clock.restart();
    }
    sf::Sprite& sprite(m_living.sprite());
    sprite.setTextureRect(sf::IntRect(
        (3 + FRAMES[m_currentFrame]) * m_living.w(),
        m_living.h() * static_cast<std::uint8_t>(m_living.direction()),
        m_living.w(),
        m_living.h()
    ));

    int xPos = m_living.x();
    int yPos = m_living.y();
    sprite.setPosition(xPos, yPos);
    window.draw(sprite);
}

void Attacking::moveTowards(std::uint16_t x, std::uint16_t y) {
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

void Attacking::walk() {
    auto self(shared_from_this());
    m_living.changeState(
        std::make_shared<LivingState::WalkingState>(m_living)
    );
}

void Attacking::stand() {
    auto self(shared_from_this());
    m_living.changeState(
        std::make_shared<LivingState::StandingState>(m_living)
    );
}

} // namespace LivingState
} // namespace Graphics
