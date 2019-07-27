#include "map_view.hpp"
#include "graphics/entity.hpp"

namespace Graphics {

Entity::Entity(const MapView& mapView,
               const std::string& chipset,
               std::size_t w,
               std::size_t h,
               std::int32_t x,
               std::int32_t y,
               std::uint16_t scaleFactor)
    : m_mapView(mapView),
      m_chipset(texture(chipset)),
      m_chipsetName(chipset),
      m_w(w),
      m_h(h),
      m_x(x),
      m_y(y),
      m_scaleFactor(scaleFactor)
{
    m_sprite.setTexture(m_chipset);
    //m_sprite.setScale(scaleFactor, scaleFactor);
}

Entity::Entity(const Entity& entity) :
    m_mapView(entity.m_mapView),
    m_chipset(texture(entity.m_chipsetName)),
    m_chipsetName(entity.m_chipsetName),
    m_w(entity.m_w),
    m_h(entity.m_h),
    m_x(entity.m_x),
    m_y(entity.m_y),
    m_scaleFactor(entity.m_scaleFactor)
{

}

void Entity::setX(std::int32_t x) {
    m_x = x;
}

void Entity::setY(std::int32_t y) {
    m_y = y;
}

void Entity::setChipsetName(const std::string& chipsetName) {
    m_chipsetName = chipsetName;
}

} // namespace Graphics
