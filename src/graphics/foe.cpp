#include "graphics/foe.hpp"

namespace Graphics {

Foe::Foe(const ::MapView& mapView,
         const std::string& chipset,
         const std::string& name,
         std::size_t w,
         std::size_t h,
         std::int32_t x,
         std::int32_t y,
         std::uint8_t floor,
         std::uint16_t scaleFactor,
         Direction direction)
    : Living(mapView, chipset, name, w, h, x, y, floor, scaleFactor),
      m_xDst(x), m_yDst(y)
{}

void Foe::draw(sf::RenderWindow& window, const ::Camera& camera) {
    const sf::Vector2u& windowSize(window.getSize());

}

void Foe::updatePosition() {
    auto delta(computeDistance());
    m_x += delta.first;
    m_y += delta.second;
    if ((m_xMovement > 0 && m_x > m_xDst) || (m_xMovement < 0 && m_x < m_xDst))
    {
        m_x = m_xDst;
    }

    if ((m_yMovement > 0 && m_y > m_yDst) || (m_yMovement < 0 && m_y < m_yDst))
    {
        m_y = m_yDst;
    }
}

} // namespace Graphics
