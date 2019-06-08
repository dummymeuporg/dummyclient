#pragma once

#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>

#include "game_element.hpp"

class Camera;
class MapView;

namespace Graphics {

class Entity : public ::GameElement {
public:
    Entity(const MapView&,
           const std::string&,
           std::size_t,
           std::size_t,
           std::size_t,
           std::size_t,
           std::size_t
    );
    Entity(const Entity&);
    const sf::Texture& chipset() const {
        return m_chipset;
    }
    sf::Sprite& sprite() {
        return m_sprite;
    }

    const std::string& chipsetName() const {
        return m_chipsetName;
    }

    std::size_t w() const {
        return m_w;
    }

    std::size_t h() const {
        return m_h;
    }

    std::size_t x() const {
        return m_x;
    }

    std::size_t y() const {
        return m_y;
    }

    void setX(std::size_t x);
    void setY(std::size_t y);
    void setChipsetName(const std::string&);

    virtual void draw(sf::RenderWindow&, const ::Camera&) = 0;
protected:
    const MapView& m_mapView;
    const sf::Texture& m_chipset;
    sf::Sprite m_sprite;
    std::string m_chipsetName;
    std::size_t m_w, m_h, m_x, m_y, m_scaleFactor;

};

} // namespace Graphics
