#include <iostream>
#include "graphics/living.hpp"
#include "graphics/living_state/standing_state.hpp"
#include "graphics/living_state/walking_state.hpp"

namespace Graphics {
namespace LivingState {


WalkingState::WalkingState(Graphics::Living& living) :
    State(living), m_currentFrame(0)
{
    m_clock.restart();
}

void WalkingState::draw(sf::RenderWindow& window) {
    static const int FRAMES[] = {1, 2, 1, 0};
    if (m_clock.getElapsedTime().asMilliseconds() >= 140) {
        ++m_currentFrame;
        if (m_currentFrame >= 4) {
            m_currentFrame = 0;
        }
        m_clock.restart();
    }
    sf::Sprite& sprite(m_living.sprite());
    sprite.setTextureRect(sf::IntRect(
        FRAMES[m_currentFrame] * m_living.w(),
        m_living.h() * static_cast<std::uint8_t>(m_living.direction()),
        m_living.w(),
        m_living.h()
    ));
    sprite.setPosition(m_living.pixelX(), m_living.pixelY());
    window.draw(sprite);
}

void WalkingState::moveTowards(std::uint16_t x, std::uint16_t y) {
    auto self(shared_from_this());
    if (m_living.x() == x && m_living.y() == y) {
        m_living.changeState(
            std::make_shared<LivingState::StandingState>(m_living)
        );
    } else {
        if (m_living.y() < y) {
            m_living.setDirection(Dummy::Core::Character::Direction::DOWN);
        } else if(m_living.y() > y) {
            m_living.setDirection(Dummy::Core::Character::Direction::UP);
        } else if (m_living.x() < x) {
            m_living.setDirection(Dummy::Core::Character::Direction::RIGHT);
        } else if (m_living.x() > x) {
            m_living.setDirection(Dummy::Core::Character::Direction::LEFT);
        }
    }
}

} // namespace LivingState
} // namespace Graphics
