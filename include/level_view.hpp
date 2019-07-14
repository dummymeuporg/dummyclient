#pragma once

#include "game_element.hpp"
#include "local/level.hpp"

using Sprites = std::vector<sf::Sprite>;

class LevelView : public GameElement {
public:
    LevelView(const Dummy::Local::Level&, std::uint16_t, std::uint16_t,
              int);
private:
    void buildBottomSprites(const Dummy::Core::GraphicLayer&);
    void buildTopSprites(const Dummy::Core::GraphicLayer&);
    const Dummy::Local::Level& m_level;
    int m_scaleFactor;
    Sprites m_topSprites;
    Sprites m_bottomSprites;
};
