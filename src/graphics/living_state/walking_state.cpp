#include <iostream>
#include "graphics/living.hpp"
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
    if (m_clock.getElapsedTime().asMilliseconds() >= 120) {
        ++m_currentFrame;
        if (m_currentFrame >= 4) {
            m_currentFrame = 0;
        }
        m_clock.restart();
    }
    sf::Sprite& sprite(m_living.sprite());
    sprite.setTextureRect(sf::IntRect(
        FRAMES[m_currentFrame] * m_living.w(),
        m_living.h() * m_living.direction(),
        m_living.w(),
        m_living.h()
    ));
    sprite.setPosition(m_living.x(), m_living.y());
    window.draw(sprite);
}

} // namespace LivingState
} // namespace Graphics
