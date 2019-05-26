#pragma once
#include <memory>

#include "core/graphic_map.hpp"
#include "game_element.hpp"

using Sprites = std::vector<sf::Sprite>;

class MapView : public GameElement {
public:
    MapView(std::unique_ptr<const Dummy::Core::GraphicMap>);

private:
    void _load();
    void _loadLayer(const Dummy::Core::GraphicLayer&, Sprites&);
    std::unique_ptr<const Dummy::Core::GraphicMap> m_graphicMap;
    const sf::Texture& m_chipset;
    Sprites firstLayerSprites;
    Sprites secondLayerSprites;
    Sprites thirdLayerSprites;
    Sprites fourthLayerSprites;
};
