#include <iostream>

#include <boost/range/irange.hpp>
#include "graphics/map.hpp"
#include "map_view.hpp"

MapView::MapView(std::unique_ptr<const Graphics::Map> graphicMap)
    : m_map(std::move(graphicMap)),
      m_chipset(texture(m_map->chipset()))
{
    std::cerr << "Map width: " << m_map->width() << std::endl;
    std::cerr << "Map height: " << m_map->height() << std::endl;

    load();
}

void MapView::load() {
    // XXX: fix this.
    for (const auto& level: m_map->levels()) {
        m_levelViews.push_back(
            LevelView(level, level.width(), level.height())
        );
    }
}


bool MapView::blocksAt(
    std::uint8_t floor,
    std::uint32_t x,
    std::uint32_t y
) const {
    return m_map->isBlocking(
        floor,
        x / (8),
        y / (8)
    );
}

