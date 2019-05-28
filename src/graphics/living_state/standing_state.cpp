#include <iostream>
#include "graphics/living.hpp"
#include "graphics/living_state/standing_state.hpp"

namespace Graphics {
namespace LivingState {

StandingState::StandingState(Graphics::Living& living) :
    State(living)
{
}

void StandingState::draw(sf::RenderWindow& window) {
    sf::Sprite& sprite(m_living.sprite());
    sprite.setTextureRect(sf::IntRect(
        m_living.w(), m_living.h() * m_living.direction(),
        m_living.w(), m_living.h()
    ));
    sprite.setPosition(m_living.x(), m_living.y());
    window.draw(sprite);
}

} // namespace LivingState
} // namespace Graphics
