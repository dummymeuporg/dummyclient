#pragma once

#include <dummy/core/graphic_layer.hpp>
#include <dummy/local/map.hpp>

namespace Dummy {
namespace Local {
class Project;
} // namespace Local
} // namespace Dummy

namespace Graphics {

using GraphicLayers = std::map<std::int8_t, Dummy::Core::GraphicLayer>;

class Map : protected Dummy::Local::Map {
public:
    Map(const Dummy::Local::Project&, const std::string&);
    const GraphicLayers& graphicLayers(std::uint8_t) const;

    std::uint16_t width() const {
        return Dummy::Core::Map::width();
    }

    std::uint16_t height() const {
        return Dummy::Core::Map::height();
    }

    const std::string& chipset() const {
        return Dummy::Local::Map::chipset();
    }

    const std::string& music() const {
        return Dummy::Local::Map::music();
    }

    void load() {
        Dummy::Local::Map::load();
    }

    const Dummy::Local::Floors& floors() const {
        return Dummy::Local::Map::floors();
    }

    const bool
    isBlocking(std::uint8_t floor, std::uint16_t x, std::uint16_t y) const {
        return m_floors[floor].isBlocking(x, y);
    }
};

} // namespace Graphics
