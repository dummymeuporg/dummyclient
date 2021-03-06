#pragma once

#include "game_element.hpp"
#include <dummy/local/floor.hpp>

using RenderTextures = std::vector<std::unique_ptr<sf::RenderTexture>>;
using Sprites = std::vector<sf::Sprite>;
using BlockingSquares = std::vector<sf::RectangleShape>;

class FloorView : public ::GameElement {
public:
    FloorView(const Dummy::Local::Floor&, std::uint16_t, std::uint16_t);
    Sprites& topSprites() {
        return m_topSprites;
    }

    Sprites& bottomSprites() {
        return m_bottomSprites;
    }

    BlockingSquares& blockingSquares() {
        return m_blockingSquares;
    }

    const Dummy::Local::Events& touchEvents() const {
        return m_floor.touchEvents();
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
    const Dummy::Local::Floor& m_floor;
    RenderTextures m_topTextures;
    RenderTextures m_bottomTextures;

    Sprites m_topSprites;
    Sprites m_bottomSprites;

    BlockingSquares m_blockingSquares;


    const sf::Texture& m_chipset;
};
