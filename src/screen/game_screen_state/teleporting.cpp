#include <dummy/server/response/teleport_map.hpp>

#include "client.hpp"
#include "screen/loading_screen.hpp"
#include "screen/game_screen_state/teleporting.hpp"

namespace Screen {
namespace GameScreenState {

Teleporting::Teleporting(GameScreen& gameScreen) : State(gameScreen)
{}

void Teleporting::draw(sf::RenderWindow&) {
    // Nothing to do.
}

void Teleporting::tick() {
    // Nothing to do.
}

void Teleporting::loaded() {
    // Nothing to do.
}

void
Teleporting::visitResponse(const Dummy::Server::Response::Ping&) {
    // Nothing to do.
}

void
Teleporting::visitResponse(const Dummy::Server::Response::Message&) {
    // Nothing to do.
}

void
Teleporting::visitResponse(const Dummy::Server::Response::SetPosition&) {
    // Nothing to do.
}

void Teleporting::visitResponse(
    const Dummy::Server::Response::TeleportMap& teleportMap
)
{
    std::cerr << "Teleport map response" << std::endl;
    if (teleportMap.status() == 0) {
        auto screen = std::make_shared<LoadingScreen>(
            m_game, m_client, m_client.character()->mapLocation(), "main"
        );
        m_client.setScreen(screen);
    }
}

void
Teleporting::visitResponse(const Dummy::Server::Response::ChangeCharacter&) {
    // Nothing to do.
}

void Teleporting::onMessage(const std::string &) {
    // Nothing to do.
}
void Teleporting::handleCustomEvent(const ::CustomEvent &) {
    // Nothing to do.
}

void Teleporting::onTeleport(
    const std::string&,
    std::uint16_t,
    std::uint16_t,
    std::uint8_t
) {
    // Nothing to do.
}

bool Teleporting::handleEvent(const sf::Event&) {
    return true;
}

}
}
