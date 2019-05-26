#include <iostream>

#include <boost/range/irange.hpp>
#include "map_view.hpp"

MapView::MapView(std::unique_ptr<const Dummy::Core::GraphicMap> graphicMap)
    : m_graphicMap(std::move(graphicMap)),
      m_chipset(texture(graphicMap->chipset()))
{

}

void MapView::_load() {
    _loadLayer(m_graphicMap->firstLayer(), firstLayerSprites);
    _loadLayer(m_graphicMap->secondLayer(), secondLayerSprites);
    _loadLayer(m_graphicMap->thirdLayer(), thirdLayerSprites);
    _loadLayer(m_graphicMap->fourthLayer(), fourthLayerSprites);
}

void
MapView::_loadLayer(const Dummy::Core::GraphicLayer& layer, Sprites& sprites) {
    for (const auto i: boost::irange(layer.size())) {
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


