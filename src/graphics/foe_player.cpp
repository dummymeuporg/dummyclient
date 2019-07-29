#include "graphics/foe_player.hpp"

namespace Graphics {

FoePlayer::FoePlayer(
    const ::MapView& mapView,
    const std::string& chipset,
    const std::string& name,
    std::int32_t x,
    std::int32_t y,
    std::uint8_t floor,
    std::uint16_t scaleFactor,
    Direction direction
) : Foe(mapView, chipset, name, 24, 32, x, y, floor, scaleFactor, direction) {}


void FoePlayer::draw(sf::RenderWindow& window) {
    Living::draw(window);
    const sf::Vector2u& windowSize(window.getSize());

    // XXX: Duplicate with the Player class. Find a way to factorize it.
    sf::FloatRect textRect = m_displayName.getLocalBounds();
    const auto& origin(m_sprite.getOrigin());

    m_displayName.setOrigin(
        textRect.left + (textRect.width/2.0),
        textRect.top
    );

    m_displayName.setPosition((m_x - origin.x) + m_w/2.0, m_y + (m_h/3.0));
    window.draw(m_displayName);
}

} // namespace Graphics

