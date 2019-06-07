#include <iostream>

#include "server/command/teleport_map.hpp"
#include "server/response/teleport_map.hpp"
#include "game.hpp"
#include "client.hpp"
#include "client_state/playing_state.hpp"
#include "screen/game_screen.hpp"
#include "screen/loading_screen.hpp"

namespace Screen {

LoadingScreen::LoadingScreen(
    ::Game& game,
    ::Client& client,
    const std::string& mapNameToLoad,
    const std::string& instance
)
    : UIScreen(game, client),
      m_mapNameToLoad(mapNameToLoad),
      m_instance(instance),
      m_label(std::make_shared<Widget::Label>()),
      m_graphicMap(nullptr),
      m_mapView(nullptr)
{
    m_label
        ->setCaption("Loading...")
        .setFontSize(50)
        .setColor(sf::Color::White)
        .setStyle(sf::Text::Bold)
        .setFont("arial.ttf");

    sf::Text& caption(m_label->caption());
    sf::FloatRect textRect = caption.getLocalBounds();
    caption.setOrigin(textRect.left + textRect.width/2.0f,
                      textRect.top + textRect.height/2.0f);
    caption.setPosition(1280/2, 960/2);

    addWidget(m_label);
}

LoadingScreen::~LoadingScreen() {

}

void LoadingScreen::loaded() {
    pushEvent(
        CustomEvent(
            reinterpret_cast<void*>(shared_from_this().get()),
            CustomEvent::LoadMapFromFile,
            reinterpret_cast<void*>(shared_from_this().get())
        )
    );
}

void LoadingScreen::handleCustomEvent(const ::CustomEvent& event)
{
	auto self(shared_from_this());
    switch(event.type()) {
    case CustomEvent::Type::LoadMapFromFile: {
        std::cerr << "Load map " << m_mapNameToLoad
            << " from file" << std::endl;
        m_graphicMap = std::move(loadGraphicMap(m_mapNameToLoad));
        pushEvent(
            CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::MapFileLoaded,
                reinterpret_cast<void*>(shared_from_this().get())
            )
        );
        break;
    }
    case CustomEvent::Type::MapFileLoaded: {
        std::cerr << "Load map view" << std::endl;
        m_mapView = std::make_unique<::MapView>(std::move(m_graphicMap));
        std::cerr << "Loaded map view." << std::endl;
        break;
    }
    case CustomEvent::Type::MapViewLoaded: {
        std::cerr << "Can display map." << std::endl;
        std::shared_ptr<Model::PlayingModel> model =
            std::make_shared<Model::PlayingModel>();

        Dummy::Server::Command::TeleportMap teleport(
            m_mapNameToLoad,
            m_client.character()->position(),
            m_instance
        );
        m_client.sendCommand(teleport);

        /*
        m_client.changeState(
            std::make_shared<ClientState::PlayingState>(m_client, model)
        );
        */
    }
    default:
        break;
    }
}

void LoadingScreen::onResponse(
    const Dummy::Server::Response::Response& response
) {
    response.accept(*this);
}

void LoadingScreen::visitResponse(
    const Dummy::Server::Response::TeleportMap& response
) {
    std::cerr << "Got teleport map response" << std::endl;
    // Switch to game screen
    std::shared_ptr<GameScreen> screen = std::make_shared<GameScreen>(
        m_game, m_client, std::move(m_mapView)
    );
    m_client.setScreen(screen);
}

} // namespace Screen
