#include "level_view.hpp"

LevelView::LevelView(
    const Dummy::Local::Level& level,
    std::uint16_t width,
    std::uint16_t height,
    int scaleFactor)
    : m_level(level), m_scaleFactor(scaleFactor),
    m_chipset(texture(m_level.map().chipset()))
{
    m_topTextures.resize(m_level.width() * m_level.height());
    m_bottomTextures.resize(m_level.width() * m_level.height());
    m_topSprites.resize(m_level.width() * m_level.height());
    m_bottomSprites.resize(m_level.width() * m_level.height());

    initSprites();

    for (const auto& [position, layer]: m_level.graphicLayers()) {
        if (position > 0) {
            applySprites(m_topTextures, layer, m_topSprites);
        } else {
            applySprites(m_bottomTextures, layer, m_bottomSprites);
        }
    }
}

void LevelView::initSprites() {
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

void LevelView::applySprites(
    RenderTextures& renderTextures,
    const Dummy::Core::GraphicLayer& graphicLayer,
    Sprites& sprites
)
{
    for (auto i = 0; i < graphicLayer.size(); ++i) {
        const auto& coords(graphicLayer[i]);
        sf::Sprite sprite;
        float scaleFactor(static_cast<float>(m_scaleFactor));
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
        float scaleFactor(static_cast<float>(m_scaleFactor));
        sprites[i].setScale(scaleFactor, scaleFactor);
        sprites[i].setTexture(renderTextures[i]->getTexture());
    }
}
