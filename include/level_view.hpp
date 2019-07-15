#pragma once

#include "game_element.hpp"
#include "local/level.hpp"

using RenderTextures = std::vector<std::unique_ptr<sf::RenderTexture>>;

class LevelView : public GameElement {
public:
    LevelView(const Dummy::Local::Level&, std::uint16_t, std::uint16_t,
              int);
private:
    /* Methods. */
    void applySprites(RenderTextures&, const Dummy::Core::GraphicLayer&);
    void initRenderTextures();

    RenderTextures& topTextures() {
        return m_topTextures;
    }

    RenderTextures& bottomTextures() {
        return m_bottomTextures;
    }

    /* Attributes. */
    const Dummy::Local::Level& m_level;
    int m_scaleFactor;
    RenderTextures m_topTextures;
    RenderTextures m_bottomTextures;
    const sf::Texture& m_chipset;
};
