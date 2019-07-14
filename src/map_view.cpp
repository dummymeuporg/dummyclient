#include <iostream>

#include <boost/range/irange.hpp>
#include "graphics/map.hpp"
#include "map_view.hpp"

MapView::MapView(std::unique_ptr<const Graphics::Map> graphicMap,
                 int scaleFactor)
    : m_map(std::move(graphicMap)),
      m_scaleFactor(scaleFactor),
      m_chipset(texture(m_map->chipset()))
{
    std::cerr << "Map width: " << m_map->width() << std::endl;
    std::cerr << "Map height: " << m_map->height() << std::endl;
    m_firstLayerSprites.resize(m_map->width() * m_map->height());
    m_secondLayerSprites.resize(
        m_map->width() * m_map->height()
    );
    m_thirdLayerSprites.resize(
        m_map->width() * m_map->height()
    );
    m_fourthLayerSprites.resize(
        m_map->width() * m_map->height()
    );
    _load();
}

void MapView::_load() {
    // XXX: fix this.
    /*
    _loadLayer(m_map->firstLayer(), m_firstLayerSprites);
    _loadLayer(m_map->secondLayer(), m_secondLayerSprites);
    _loadLayer(m_map->thirdLayer(), m_thirdLayerSprites);
    _loadLayer(m_map->fourthLayer(), m_fourthLayerSprites);
    */
}

void
MapView::_loadLayer(const Dummy::Core::GraphicLayer& layer, Sprites& sprites) {
    for (const auto y: boost::irange(m_map->height())) {
        for(const auto x: boost::irange(m_map->width())) {
            std::size_t i(y * m_map->width() + x);
            auto coords = layer[i];
            if (coords.first >= 0 && coords.second >= 0) {
                sf::Sprite& sprite(sprites[i]);
                sprite.setScale(m_scaleFactor, m_scaleFactor);
                sprite.setTexture(m_chipset);
                sprite.setTextureRect(sf::IntRect(16 * coords.first,
                                                  16 * coords.second,
                                                  16,
                                                  16));
            }
        }
    }
}

bool MapView::blocksAt(std::uint16_t x, std::uint16_t y) const {
    // XXX: fix this.
    //return m_map->isBlocking(x, y);
    return false;
}

