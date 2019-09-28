#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include "local_map_state.hpp"
#include "floor_view.hpp"
#include "map_view.hpp"
#include "graphics/player.hpp"
#include "screen/ui_screen.hpp"

class Client;
class Game;

namespace Widget {
class Chatbox;
class QuitMessage;
} // namespace Widget

namespace Dummy {
namespace Server {
namespace Response {
class ChangeCharacter;
class Message;
class Ping;
class SetPosition;
class TeleportMap;
} // namespace Response
} // namespace Server
} // namespace Dummy


namespace Screen {

class GameScreen;

namespace GameScreenState {

using GraphicLivingsMap =
    std::map<std::string, std::unique_ptr<Graphics::Living>>;

class State {
public:
    State(GameScreen&);
    virtual ~State();
    virtual void loaded() = 0;
    virtual void draw(sf::RenderWindow&) = 0;
    virtual void tick() = 0;

    virtual void
    visitResponse(const Dummy::Server::Response::Message&) = 0;

    virtual void
    visitResponse(const Dummy::Server::Response::Ping&) = 0;

    virtual void
    visitResponse(const Dummy::Server::Response::SetPosition&) = 0;

    virtual void
    visitResponse(const Dummy::Server::Response::ChangeCharacter&) = 0;

    virtual void
    visitResponse(const Dummy::Server::Response::TeleportMap&) = 0;

    virtual void onTeleport(
        const std::string&,
        std::uint16_t,
        std::uint16_t,
        std::uint8_t
    ) = 0;

    virtual void onMessage(const std::string&) = 0;
    virtual bool handleEvent(const sf::Event&) = 0;
    virtual void handleCustomEvent(const ::CustomEvent&) = 0;

protected:
    GameScreen& m_gameScreen;
    ::MapView& m_mapView;
    Graphics::Player& m_player;
    GraphicLivingsMap& m_livings;
    ::LocalMapState& m_mapState;
    sf::View& m_gameView;
    sf::View& m_hudView;
    ::Client& m_client;
    ::Game& m_game;


};

} // namespace GameScreenState
} // namespace Screen
