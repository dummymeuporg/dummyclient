#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "graphics/living.hpp"

class Camera;
class MapView;

namespace Graphics {

class Foe : public Living {
public:
    Foe(const MapView& mapView,
        const std::string& chipset,
        const std::string& name,
        std::size_t w,
        std::size_t h,
        std::int32_t x,
        std::int32_t y,
        std::uint8_t floor,
        std::uint16_t scaleFactor,
        Direction direction
    );

    void draw(sf::RenderWindow&, const ::Camera&) override;
protected:
    void updatePosition() override;
private:
    std::int32_t m_xDst, m_yDst;
};

}
