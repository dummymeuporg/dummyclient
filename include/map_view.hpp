#pragma once
#include <memory>

#include "core/graphic_map.hpp"
#include "game_element.hpp"

using Sprites = std::vector<sf::Sprite>;

class MapView : public GameElement {
public:
    MapView(std::unique_ptr<const Dummy::Core::GraphicMap>, int scaleFactor);
    Sprites& firstLayerSprites() {
        return m_firstLayerSprites;
    }

    Sprites& secondLayerSprites() {
        return m_secondLayerSprites;
    }

    Sprites& thirdLayerSprites() {
        return m_thirdLayerSprites;
    }

    Sprites& fourthLayerSprites() {
        return m_fourthLayerSprites;
    }

    std::uint16_t width() const {
        return m_graphicMap->width();
    }

    std::uint16_t height() const {
        return m_graphicMap->height();
    }

    bool blocksAt(std::uint16_t x, std::uint16_t y) const; 

private:
    void _load();
    void _loadLayer(const Dummy::Core::GraphicLayer&, Sprites&);

    /* Private members. */
    std::unique_ptr<const Dummy::Core::GraphicMap> m_graphicMap;
    int m_scaleFactor;
    const sf::Texture& m_chipset;
    Sprites m_firstLayerSprites;
    Sprites m_secondLayerSprites;
    Sprites m_thirdLayerSprites;
    Sprites m_fourthLayerSprites;
};
