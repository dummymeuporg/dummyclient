#include <boost/range/irange.hpp>

#include "game.hpp"

#include "graphics/foe.hpp"

#include "widget/quit_message.hpp"

#include "screen/game_screen.hpp"
#include "screen/game_screen_state/playing_state.hpp"

namespace Screen {
namespace GameScreenState {

void PlayingState::draw(sf::RenderWindow& window) {

    // Properties of GameScreen
    auto& gameView(m_gameScreen.gameView());
    auto& player(m_gameScreen.player());
    auto& mapView(m_gameScreen.mapView());
    auto& hudView(m_gameScreen.hudView());
    auto& isEscapeMode(m_gameScreen.isEscapeMode());
    auto quitMessage(m_gameScreen.quitMessage());

    gameView.setCenter(player.x() + 12, player.y() + 16);
    window.setView(gameView);

    for (unsigned i = 0; i < mapView.floorViews().size(); ++i) {
        drawFloorView(i, mapView.floorView(i));
    }
    //m_gameView.setCenter(m_player.x() + 12, m_player.y() + 16);
    // Draw widgets (HUD) if needed.
    window.setView(hudView);

    for (unsigned i = 0; i < mapView.floorViews().size(); ++i) {
        drawFloorViewHUD(i, mapView.floorView(i));
    }

    // XXX: ugly.
    if (isEscapeMode) {
        quitMessage->draw(window);
    }
    m_gameScreen.drawUI(window);
}

void PlayingState::drawFloorView(unsigned int index, ::FloorView& floorView) {

    auto& debugMode(m_gameScreen.debugMode());
    auto& game(m_gameScreen.game());
    auto& mapState(m_gameScreen.mapState());
    auto& player(m_gameScreen.player());

    // Draw the lower layers.
    drawSprites(floorView.bottomSprites());

    //drawLivings(index);

    // Draw the character if needed.
    if (player.floor() == index) {
        drawCharacter();
    }

    // Draw the livings on the current floor.
    const auto& localFloorState(mapState.localFloorState(index));
    for (auto& [name, foe]: localFloorState.graphicFoes()) {
        foe->draw(game.window());
    }

    drawSprites(floorView.topSprites());

    if (debugMode) {
        drawBlockingLayer(index, floorView);
    }
}

void PlayingState::drawFloorViewHUD(unsigned int index, ::FloorView& floorView)
{
    auto& game(m_gameScreen.game());
    auto& mapState(m_gameScreen.mapState());
    auto& player(m_gameScreen.player());
    auto& gameView(m_gameScreen.gameView());


    // Draw the character HUD, if needed
    if (player.floor() == index) {
        drawCharacterHUD();
    }

    // Draw the living HUD on the current floor
    const auto& localFloorState(mapState.localFloorState(index));
    for (auto& [name, foe]: localFloorState.graphicFoes()) {
        foe->drawHUD(game.window(), gameView);
    }
}

void PlayingState::drawSprites(Sprites& sprites) {
    auto& game(m_gameScreen.game());
    auto& mapView(m_gameScreen.mapView());

    const auto& height(static_cast<int>(mapView.height()));
    const auto& width(static_cast<int>(mapView.width()));
    for (const auto y: boost::irange(0, height)) {
        for(const auto x: boost::irange(0, width)) {
            std::size_t index = (y * mapView.width()) + x;
            sf::Sprite& sprite = sprites.at(index);

            int windowX = (x * 16);
            int windowY = (y * 16);

            // Only draw the sprite if it has a texture.
            if (nullptr != sprite.getTexture()) {
                sprite.setPosition(sf::Vector2f(windowX, windowY));
                game.window().draw(sprite);
            }
        }
    }
}

void PlayingState::drawBlockingLayer(unsigned int index, FloorView& floorView)
{
    auto& game(m_gameScreen.game());
    auto& mapView(m_gameScreen.mapView());

    auto maxHeight(static_cast<int>(mapView.height() * 2));
    auto maxWidth(static_cast<int>(mapView.width() * 2));
    for (const auto y: boost::irange(0, maxHeight)) {
        for(const auto x: boost::irange(0, maxWidth)) {
            std::size_t blockIndex = (y * mapView.width() * 2) + x;
            if (mapView.blocksAt(index, x*8, y*8)) {
                auto& blockingSquare(floorView.blockingSquares().at(blockIndex));
                blockingSquare.setPosition(x * 8, y * 8);
                game.window().draw(blockingSquare);
            }
        }
    }
}


void PlayingState::drawCharacter() {
    auto& player(m_gameScreen.player());
    auto& game(m_gameScreen.game());
    player.draw(game.window());
}

void PlayingState::drawCharacterHUD() {
    auto& player(m_gameScreen.player());
    auto& game(m_gameScreen.game());
    auto& gameView(m_gameScreen.gameView());

    player.drawHUD(game.window(), gameView);
}

} // namespace GameScreenState
} // namespace State
