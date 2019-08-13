#include "floor_view.hpp"

FloorView::FloorView(
    const Dummy::Local::Floor& floor,
    std::uint16_t width,
    std::uint16_t height)
    : m_floor(floor), m_chipset(texture(m_floor.map().chipset()))
{
    m_topTextures.resize(m_floor.width() * m_floor.height());
    m_bottomTextures.resize(m_floor.width() * m_floor.height());
    m_topSprites.resize(m_floor.width() * m_floor.height());
    m_bottomSprites.resize(m_floor.width() * m_floor.height());
    m_blockingSquares.resize(m_floor.width() * m_floor.height() * 4);

    initSprites();

    for (const auto& [position, layer]: m_floor.graphicLayers()) {
        if (position > 0) {
            applySprites(m_topTextures, layer, m_topSprites);
        } else {
            applySprites(m_bottomTextures, layer, m_bottomSprites);
        }
    }

    initBlockingSprites();
}

void FloorView::initSprites() {
    for (auto& renderTexture : m_topTextures) {
        renderTexture = std::make_unique<sf::RenderTexture>();
        renderTexture->create(16, 16);
        //renderTexture->clear(sf::Color::Black);
    }

    for (auto& renderTexture : m_bottomTextures) {
        renderTexture = std::make_unique<sf::RenderTexture>();
        renderTexture->create(16, 16);
        //renderTexture->clear(sf::Color::Black);
    }
}

void FloorView::initBlockingSprites()
{
    for (unsigned i = 0; i < m_floor.blockingLayer().size(); ++i) {
        m_blockingSquares[i].setSize(sf::Vector2f(8, 8));
        m_blockingSquares[i].setFillColor(sf::Color(255, 0, 0, 127));
    }
}

void FloorView::applySprites(
    RenderTextures& renderTextures,
    const Dummy::Core::GraphicLayer& graphicLayer,
    Sprites& sprites
)
{
    for (auto i = 0; i < graphicLayer.size(); ++i) {
        const auto& coords(graphicLayer[i]);
        sf::Sprite sprite;
        if (coords.first >= 0 && coords.second >= 0) {
            sprite.setTexture(m_chipset);
            sprite.setTextureRect(
                sf::IntRect(
                    16 * coords.first,
                    16 * coords.second,
                    16,
                    16
                )
            );
            renderTextures[i]->draw(sprite);
            renderTextures[i]->display();
        }
    }

    // Now, generate sprites from render textures.
    for (auto i = 0; i < sprites.size(); ++i) {
        const auto& coords(graphicLayer[i]);

        //sprites[i].setScale(scaleFactor, scaleFactor);

        if (coords.first >= 0 && coords.second >= 0) {
            sprites[i].setTexture(renderTextures[i]->getTexture());
        }
    }
}
