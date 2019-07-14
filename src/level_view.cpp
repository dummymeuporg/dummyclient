#include "level_view.hpp"

LevelView::LevelView(
    const Dummy::Local::Level& level,
    std::uint16_t width,
    std::uint16_t height,
    int scaleFactor)
    : m_level(level), m_scaleFactor(scaleFactor)
{
    for (const auto& [position, layer]: m_level.graphicLayers()) {
        if (position > 0) {
            // XXX: build top sprites.
            buildTopSprites(layer);
        } else {
            // XXX: build bottom sprites.
            buildBottomSprites(layer);
        }
    }
}

void
LevelView::buildBottomSprites(const Dummy::Core::GraphicLayer& graphicLayer) {

}

void
LevelView::buildTopSprites(const Dummy::Core::GraphicLayer& graphicLayer) {

}
