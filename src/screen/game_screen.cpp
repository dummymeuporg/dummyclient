#include <cmath>
#include <iostream>

#include <boost/range/irange.hpp>

#include <dummy/server/command/change_character.hpp>
#include <dummy/server/command/message.hpp>
#include <dummy/server/command/ping.hpp>
#include <dummy/server/command/teleport_map.hpp>

#include <dummy/server/response/change_character.hpp>
#include <dummy/server/response/message.hpp>
#include <dummy/server/response/ping.hpp>
#include <dummy/server/response/teleport_map.hpp>

#include "widget/button.hpp"
#include "widget/chatbox.hpp"
#include "widget/quit_message.hpp"

#include "client.hpp"
#include "game.hpp"
#include "graphics/foe.hpp"
#include "graphics/living_state/standing_state.hpp"
#include "graphics/living_state/walking_state.hpp"
#include "floor_view.hpp"

#include "screen/game_screen.hpp"
#include "screen/loading_screen.hpp"

#include "screen/game_screen_state/playing.hpp"

namespace Screen {

GameScreen::GameScreen(
    ::Game& game,
    ::Client& client,
    std::unique_ptr<::MapView> mapView
)
    : UIScreen(game, client),
      m_mapView(std::move(mapView)),
      m_player(
          *m_mapView,
          m_client,
          m_client.character()->skin(),
          m_client.character()->name(),
          m_client.character()->position().first,
          m_client.character()->position().second,
          m_client.character()->floor(),
          game.scaleFactor(),
          m_client.character()->direction()
      ),
      m_mapState(*m_mapView),
      m_gameView(sf::FloatRect(0,
                               0,
                               m_game.width(),
                               m_game.height())),
      m_hudView(sf::FloatRect(0,
                              0,
                              m_game.windowWidth(),
                              m_game.windowHeight())),
      m_state(std::make_shared<GameScreenState::Playing>(*this))

{
}

GameScreen::~GameScreen() {
}

void GameScreen::loaded() {
    m_state->loaded();
}

bool GameScreen::handleCustomEvent(const ::CustomEvent& event) {
    /*
    bool forward(UIScreen::handleCustomEvent(event));
    if (!forward) {
        return forward;
    }
    return m_state->handleCustomEvent(event);
    */
    bool forward = m_state->handleCustomEvent(event);
    if (!forward) {
        return forward;
    }
    return UIScreen::handleCustomEvent(event);
}

bool GameScreen::handleEvent(const sf::Event& event) {
    bool forward = UIScreen::handleEvent(event);
    if (!forward) {
        return forward;
    }
    return m_state->handleEvent(event);
}


void GameScreen::draw(sf::RenderWindow& window) {
    m_state->draw(window);
}

void GameScreen::drawUI(sf::RenderWindow& window) {
    UIScreen::draw(window);
}

void GameScreen::tick() {
    m_state->tick();
}


void GameScreen::onResponse(
    const Dummy::Server::Response::Response& response
) {
    response.accept(*this);
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::SetPosition& setPosition
) {
    m_state->visitResponse(setPosition);
}


void GameScreen::visitResponse(
    const Dummy::Server::Response::Ping& ping
) {
    m_state->visitResponse(ping);
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::Message& message
) {
    m_state->visitResponse(message);
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::ChangeCharacter& changeCharacter
)
{
    auto self(shared_from_this());
    m_state->visitResponse(changeCharacter);
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::TeleportMap& teleportMap
)
{
    auto self(shared_from_this());
    m_state->visitResponse(teleportMap);
}

void GameScreen::onMessage(const std::string& message) {
    m_state->onMessage(message);
}

void GameScreen::addWidget(std::shared_ptr<Widget::Abstract::Widget> widget) {
    UIScreen::addWidget(widget);
}

void GameScreen::onTeleport(
    const std::string& destinationMap,
    std::uint16_t x,
    std::uint16_t y,
    std::uint8_t floor
) {
    m_state->onTeleport(destinationMap, x, y, floor);
}

void GameScreen::pushEvent(CustomEvent&& customEvent) {
    GameElement::pushEvent(std::move(customEvent));
}

void GameScreen::setState(std::shared_ptr<GameScreenState::State> state) {
    m_state = state;
}

} // namespace Screen
