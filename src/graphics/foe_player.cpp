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
    m_displayName.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top
    );
    m_displayName.setPosition(
        static_cast<int>(windowSize.x / 2) + m_x +
        w() * 1,
        static_cast<int>(windowSize.y / 2) + m_y +
        h() * 2
    );
    window.draw(m_displayName);
}

} // namespace Graphics

