#pragma once

#include "game_element.hpp"
#include <dummy/local/level.hpp>

using RenderTextures = std::vector<std::unique_ptr<sf::RenderTexture>>;
using Sprites = std::vector<sf::Sprite>;
using BlockingSquares = std::vector<sf::RectangleShape>;

class LevelView : public ::GameElement {
public:
    LevelView(const Dummy::Local::Level&, std::uint16_t, std::uint16_t);
    Sprites& topSprites() {
        return m_topSprites;
    }

    Sprites& bottomSprites() {
        return m_bottomSprites;
    }

    BlockingSquares& blockingSquares() {
        return m_blockingSquares;
    }

private:
    /* Methods. */
    void applySprites(
        RenderTextures&,
        const Dummy::Core::GraphicLayer&,
        Sprites&
    );
    void initSprites();
    void initBlockingSprites();


    /* Attributes. */
    const Dummy::Local::Level& m_level;
    RenderTextures m_topTextures;
    RenderTextures m_bottomTextures;

    Sprites m_topSprites;
    Sprites m_bottomSprites;

    BlockingSquares m_blockingSquares;


    const sf::Texture& m_chipset;
};
