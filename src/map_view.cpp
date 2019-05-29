#include <iostream>

#include <boost/range/irange.hpp>
#include "map_view.hpp"

MapView::MapView(std::unique_ptr<const Dummy::Core::GraphicMap> graphicMap)
    : m_graphicMap(std::move(graphicMap)),
      m_chipset(texture(m_graphicMap->chipset()))
{
    std::cerr << "Map width: " << m_graphicMap->width() << std::endl;
    std::cerr << "Map height: " << m_graphicMap->height() << std::endl;
    m_firstLayerSprites.resize(m_graphicMap->width() * m_graphicMap->height());
    m_secondLayerSprites.resize(
        m_graphicMap->width() * m_graphicMap->height()
    );
    m_thirdLayerSprites.resize(
        m_graphicMap->width() * m_graphicMap->height()
    );
    m_fourthLayerSprites.resize(
        m_graphicMap->width() * m_graphicMap->height()
    );
    _load();
}

void MapView::_load() {
    _loadLayer(m_graphicMap->firstLayer(), m_firstLayerSprites);
    _loadLayer(m_graphicMap->secondLayer(), m_secondLayerSprites);
    _loadLayer(m_graphicMap->thirdLayer(), m_thirdLayerSprites);
    _loadLayer(m_graphicMap->fourthLayer(), m_fourthLayerSprites);
}

void
MapView::_loadLayer(const Dummy::Core::GraphicLayer& layer, Sprites& sprites) {
    for (const auto y: boost::irange(m_graphicMap->height())) {
        for(const auto x: boost::irange(m_graphicMap->width())) {
            std::size_t i(y * m_graphicMap->width() + x);
            auto coords = layer[i];
            if (coords.first >= 0 && coords.second >= 0) {
                sf::Sprite& sprite(sprites[i]);
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
    return m_graphicMap->isBlocking(x, y);
}

