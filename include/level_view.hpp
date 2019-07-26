#pragma once

#include "game_element.hpp"
#include <dummy/local/level.hpp>

using RenderTextures = std::vector<std::unique_ptr<sf::RenderTexture>>;
using Sprites = std::vector<sf::Sprite>;

class LevelView : public ::GameElement {
public:
    LevelView(const Dummy::Local::Level&, std::uint16_t, std::uint16_t,
              int);
    Sprites& topSprites() {
        return m_topSprites;
    }

    Sprites& bottomSprites() {
        return m_bottomSprites;
    }
private:
    /* Methods. */
    void applySprites(
        RenderTextures&,
        const Dummy::Core::GraphicLayer&,
        Sprites&
    );
    void initSprites();


    /* Attributes. */
    const Dummy::Local::Level& m_level;
    int m_scaleFactor;
    RenderTextures m_topTextures;
    RenderTextures m_bottomTextures;

    Sprites m_topSprites;
    Sprites m_bottomSprites;

    const sf::Texture& m_chipset;
};
