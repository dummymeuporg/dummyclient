#include <iostream>

#include "client.hpp"
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

void GameScreen::draw() {
    // Draw the map
    
    // Draw widgets (HUD) if needed.
    UIScreen::draw();
}

} // namespace Screen
