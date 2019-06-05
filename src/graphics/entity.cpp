#include "graphics/entity.hpp"

namespace Graphics {

Entity::Entity(const std::string& chipset,
               std::size_t w,
               std::size_t h,
               std::size_t x,
               std::size_t y,
               std::size_t scaleFactor)
    : m_chipset(texture(chipset)), m_chipsetName(chipset), m_w(w), m_h(h),
      m_x(x), m_y(y), m_scaleFactor(scaleFactor), m_pixelX(0), m_pixelY(0)
{
    m_sprite.setTexture(m_chipset);
    m_sprite.setScale(scaleFactor, scaleFactor);
}

Entity::Entity(const Entity& entity) :
    m_chipset(texture(entity.m_chipsetName)),
    m_chipsetName(entity.m_chipsetName),
    m_w(entity.m_w),
    m_h(entity.m_h),
    m_x(entity.m_x),
    m_y(entity.m_y),
    m_scaleFactor(entity.m_scaleFactor),
    m_pixelX(entity.m_pixelX),
    m_pixelY(entity.m_pixelY)

{

}

void Entity::setX(std::size_t x) {
    m_x = x;
}

void Entity::setY(std::size_t y) {
    m_y = y;
}

void Entity::setPixelPosition(int x, int y) {
    m_pixelX = x;
    m_pixelY = y;
}
void Entity::setPixelX(int x) {
    m_pixelX = x;
}

void Entity::setPixelY(int y) {
    m_pixelY = y;
}

void Entity::setPixelPosition(const std::pair<int, int>& pair) {
    setPixelPosition(pair.first, pair.second);
}

void Entity::setChipsetName(const std::string& chipsetName) {
    m_chipsetName = chipsetName;
}

} // namespace Graphics
