#include <iostream>

#include <boost/range/irange.hpp>

#include "client.hpp"
#include "game.hpp"
#include "model/loading_model.hpp"

#include "screen/game_screen.hpp"

namespace Screen {

GameScreen::GameScreen(
    ::Game& game,
    ::Client& client,
    std::unique_ptr<::MapView> mapView
)
    : UIScreen(game, client), m_mapView(std::move(mapView))
{
}

void GameScreen::loaded() {

}

void GameScreen::notify() {

}

void GameScreen::handleCustomEvent(const ::CustomEvent& event) {

}

void GameScreen::_drawLayer(::Sprites& sprites) {
    const std::pair<std::uint16_t, std::uint16_t>& position(
        m_client.pixelPosition()
    );
    for(const auto x: boost::irange(m_mapView->width())) {
        for (const auto y: boost::irange(m_mapView->height())) {
            std::size_t index = y * m_mapView->width() + x;
            sf::Sprite& sprite = sprites.at(index);
            sprite.setScale(4, 4);
            sprite.setPosition(sf::Vector2f(
                ((x * 64) - position.first) + (1280/2) - 32,
                ((y * 64) - position.second) + (960/2) - 32)
            );
            m_game.window().draw(sprite);
        }
    }
}

void GameScreen::_drawCharacter() {
    sf::Sprite sprite;
    sprite.setTexture(texture(m_client.character()->skin()));
    sprite.setScale(4, 4);
    sprite.setTextureRect(sf::IntRect(24, 32 * 2, 24, 32));
    sprite.setPosition(1280/2 - 12, 960/2 - 16);
    m_game.window().draw(sprite);
}

void GameScreen::draw() {
    // Draw the map
    _drawLayer(m_mapView->firstLayerSprites());
    _drawLayer(m_mapView->secondLayerSprites());
    _drawCharacter();
    _drawLayer(m_mapView->thirdLayerSprites());
    _drawLayer(m_mapView->fourthLayerSprites());
    // Draw widgets (HUD) if needed.
    UIScreen::draw();
}

} // namespace Screen
