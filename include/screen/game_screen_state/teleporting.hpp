#pragma once

#include "screen/game_screen_state/state.hpp"

namespace Screen {
namespace GameScreenState {

class Teleporting : public State {
public:
    Teleporting(GameScreen&);
    void draw(sf::RenderWindow &) override;
    void tick() override;
    void loaded() override;

    void
    visitResponse(const Dummy::Server::Response::Ping &) override;

    void
    visitResponse(const Dummy::Server::Response::Message &) override;

    void
    visitResponse(const Dummy::Server::Response::SetPosition &) override;

    void
    visitResponse(const Dummy::Server::Response::TeleportMap &) override;

    void
    visitResponse(const Dummy::Server::Response::ChangeCharacter &) override;

    void onMessage(const std::string&) override;
    bool handleCustomEvent(const ::CustomEvent &) override;

    void onTeleport(
        const std::string&,
        std::uint16_t,
        std::uint16_t,
        std::uint8_t
    ) override;

    bool handleEvent(const sf::Event&) override;
};

} // namespace GameScreenState
} // namespace Screen
