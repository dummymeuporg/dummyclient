#pragma once
#include <memory>

#include "level_view.hpp"
#include "graphics/map.hpp"
#include "game_element.hpp"


using Sprites = std::vector<sf::Sprite>;
using LevelViews = std::vector<::LevelView>;

class MapView : public GameElement {
public:
    MapView(std::unique_ptr<const Graphics::Map>, int scaleFactor);

    std::uint16_t width() const {
        return m_map->width();
    }

    std::uint16_t height() const {
        return m_map->height();
    }

    bool blocksAt(std::uint16_t x, std::uint16_t y) const; 

    int scaleFactor() const {
        return m_scaleFactor;
    }

    const LevelViews& levelViews() const {
        return m_levelViews;
    }

    LevelView& levelView(unsigned i) {
        return m_levelViews[i];
    }

private:
    void load();

    /* Private members. */
    std::unique_ptr<const Graphics::Map> m_map;
    int m_scaleFactor;
    const sf::Texture& m_chipset;
    LevelViews m_levelViews;

};
