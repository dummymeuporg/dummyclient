#include "graphics/foe.hpp"

namespace Graphics {

Foe::Foe(const ::MapView& mapView,
         const std::string& chipset,
         std::size_t w,
         std::size_t h,
         std::int32_t x,
         std::int32_t y,
         std::uint8_t floor,
         std::uint16_t scaleFactor,
         Direction direction)
    : Living(mapView, chipset, w, h, x, y, floor, scaleFactor),
      m_xDst(x), m_yDst(y)
{}


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

    if (m_x == m_xDst && m_y == m_yDst) {
        stand();
    } else {
        walk();
    }
}

void Foe::setXDst(std::int32_t xDst) {
    m_xDst = xDst;
}

void Foe::setYDst(std::int32_t yDst) {
    m_yDst = yDst;
}

} // namespace Graphics
