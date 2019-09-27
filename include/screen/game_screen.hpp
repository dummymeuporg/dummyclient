#pragma once

#include <dummy/local/event_observer.hpp>

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

namespace Screen {

namespace GameScreenState {
class State;
} // namespace GameScreenState

using GraphicLivingsMap = 
    std::map<std::string, std::unique_ptr<Graphics::Living>>;

class GameScreen : public UIScreen, public Dummy::Local::EventObserver {
public:


    GameScreen(::Game&,
               ::Client&,
               std::unique_ptr<::MapView>);
    ~GameScreen() override;
    void loaded() override;
    bool handleEvent(const sf::Event&) override;
    void handleCustomEvent(const ::CustomEvent&) override;
    void draw(sf::RenderWindow&) override;
    void tick() override;


    void
    onResponse(const Dummy::Server::Response::Response& response) override;

    void visitResponse(const Dummy::Server::Response::Message&) override;
    void visitResponse(const Dummy::Server::Response::Ping&) override;
    void visitResponse(const Dummy::Server::Response::SetPosition&) override;
    void
    visitResponse(const Dummy::Server::Response::ChangeCharacter&) override;
    void visitResponse(const Dummy::Server::Response::TeleportMap&) override;

    // EventObserver
    void onMessage(const std::string&) override;
    void onTeleport(
        const std::string&,
        std::uint16_t,
        std::uint16_t,
        std::uint8_t
    ) override;

    // Helpers for states.
    void drawUI(sf::RenderWindow&);
    void pushEvent(CustomEvent&&);
    void addWidget(std::shared_ptr<Widget::Abstract::Widget>);

    // XXX: Accessors: should only be accessed by the GameScreenStates.
    sf::View& gameView() {
        return m_gameView;
    }

    sf::View& hudView() {
        return m_hudView;
    }

    ::LocalMapState& mapState() {
        return m_mapState;
    }

    Graphics::Player& player() {
        return m_player;
    }

    ::MapView& mapView() {
        return *m_mapView;
    }

    GraphicLivingsMap livings() {
        return m_livings;
    }

    ::Client& client() {
        return m_client;
    }

    // XXX: End of accessors.



private:

    /* Private attributes. */
    std::unique_ptr<::MapView> m_mapView;
    Graphics::Player m_player;
    GraphicLivingsMap m_livings;
    ::LocalMapState m_mapState;
    sf::View m_gameView, m_hudView;
    std::shared_ptr<GameScreenState::State> m_state;

    // XXX: I am going to puke. LOL.
};

} // namespace Screen
