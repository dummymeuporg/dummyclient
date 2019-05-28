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
    : UIScreen(game, client), m_mapView(std::move(mapView)),
      m_originX((game.width() / 2) - 48),
      m_originY((game.height() / 2) - 64),
      m_player(m_client, m_client.character()->skin(), m_originX, m_originY)
{
}

void GameScreen::loaded() {

}

void GameScreen::notify() {

}

void GameScreen::handleCustomEvent(const ::CustomEvent& event) {

}

void GameScreen::handleEvent(const sf::Event& event)
{
    switch(event.type) {
    case sf::Event::KeyPressed:
        _onKeyPressed(event);
        break;
    default:
        break;
    }
}

void GameScreen::_onKeyPressed(const sf::Event& event) {
    switch(event.key.code) {
    case sf::Keyboard::Up:
        m_client.moveUp(*m_mapView);
        break;
    case sf::Keyboard::Right:
        m_client.moveRight(*m_mapView);
        break;
    case sf::Keyboard::Down:
        m_client.moveDown(*m_mapView); 
        break;
    case sf::Keyboard::Left:
        m_client.moveLeft(*m_mapView);
        break;
    default:
        break;
    }
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
            sprite.setPosition(
                sf::Vector2f(
                    m_originX + ((x * 64) - position.first + 16),
                    m_originY + ((y * 64) - position.second + 96)
                )
            );
            m_game.window().draw(sprite);
        }
    }
}

void GameScreen::_drawCharacter() {
    m_player.draw(m_game.window());
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
