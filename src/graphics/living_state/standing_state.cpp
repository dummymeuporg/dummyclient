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

void StandingState::draw(sf::RenderWindow& window, const ::Camera& camera) {
    const sf::Vector2u& windowSize(window.getSize());
    sf::Sprite& sprite(m_living.sprite());
    sprite.setTextureRect(sf::IntRect(
        m_living.w(),
        m_living.h() * static_cast<std::uint8_t>(m_living.direction()),
        m_living.w(),
        m_living.h()
    ));
    sprite.setPosition(
        (windowSize.x / 2) +
            m_living.pixelX() - static_cast<int>(camera.centerX()),
        (windowSize.y / 2) +
            m_living.pixelY() - static_cast<int>(camera.centerY())
    );
    window.draw(sprite);
}

void StandingState::moveTowards(std::uint16_t x, std::uint16_t y) {
    auto self(shared_from_this());
    if (m_living.x() != x || m_living.y() != y) {
        m_living.changeState(
            std::make_shared<LivingState::WalkingState>(m_living)
        );
    }
}

} // namespace LivingState
} // namespace Graphics
