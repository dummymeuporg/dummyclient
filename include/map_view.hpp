#pragma once
#include <memory>

#include "floor_view.hpp"
#include "graphics/map.hpp"
#include "game_element.hpp"


using Sprites = std::vector<sf::Sprite>;
using FloorViews = std::vector<::FloorView>;

class MapView : public GameElement {
public:
    MapView(std::unique_ptr<Graphics::Map>);

    std::uint16_t width() const {
        return m_map->width();
    }

    std::uint16_t height() const {
        return m_map->height();
    }

    bool blocksAt(std::uint8_t, std::uint32_t, std::uint32_t) const;

    int scaleFactor() const {
        return m_scaleFactor;
    }

    const FloorViews& floorViews() const {
        return m_floorViews;
    }

    FloorView& floorView(unsigned i) {
        return m_floorViews[i];
    }

    Graphics::Map& map() {
        return *m_map;
    }

private:
    void load();

    /* Private members. */
    std::unique_ptr<Graphics::Map> m_map;
    int m_scaleFactor;
    const sf::Texture& m_chipset;
    FloorViews m_floorViews;

};
