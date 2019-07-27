#pragma once

#include "graphics/foe.hpp"

namespace Graphics {

class FoePlayer : public Foe {
public:
    FoePlayer(
        const MapView& mapView,
        const std::string& chipset,
        const std::string& name,
        std::int32_t x,
        std::int32_t y,
        std::uint8_t floor,
        std::uint16_t scaleFactor,
        Direction direction
    );

    void draw(sf::RenderWindow&) override;
};

} // namespace Graphics
