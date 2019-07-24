#pragma once

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


    std::int32_t xDst() const {
        return m_xDst;    
    }

    std::int32_t yDst() const {
        return m_yDst;
    }

    void setXDst(std::int32_t);
    void setYDst(std::int32_t);

protected:
    void updatePosition() override;
private:
    std::int32_t m_xDst, m_yDst;
};

}
