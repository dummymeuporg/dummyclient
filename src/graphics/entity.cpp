#include "graphics/entity.hpp"

namespace Graphics {

Entity::Entity(const std::string& chipset,
               std::size_t w,
               std::size_t h,
               std::size_t x,
               std::size_t y)
    : m_chipset(texture(chipset)), m_chipsetName(chipset), m_w(w), m_h(h),
      m_x(x), m_y(y)
{
    m_sprite.setTexture(m_chipset);
    m_sprite.setScale(4, 4);
}

void Entity::setX(std::size_t x) {
    m_x = x;
}

void Entity::setY(std::size_t y) {
    m_y = y;
}

void Entity::setChipsetName(const std::string& chipsetName) {
    m_chipsetName = chipsetName;
}

} // namespace Graphics
