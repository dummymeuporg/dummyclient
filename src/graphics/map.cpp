#include "graphics/map.hpp"
#include <dummy/local/project.hpp>

namespace Graphics {

Map::Map(const Dummy::Local::Project& localProject, const std::string& mapName)
    : Dummy::Local::Map(localProject, mapName)
{}

} // namespace Graphics
