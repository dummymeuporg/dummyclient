#include <dummy/protocol/bridge.hpp>
#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/server/command/command.hpp>
#include <dummy/server/command/teleport_map.hpp>
#include <dummy/server/response/teleport_map.hpp>
#include "connector/network_connector.hpp"
#include "connector/network_connector_state/loading_state.hpp"
#include "connector/network_connector_state/playing_state.hpp"

namespace Connector {
namespace NetworkConnectorState {

LoadingState::LoadingState(NetworkConnector& networkConnector)
    : State(networkConnector)
{

}

void
LoadingState::sendCommand(
    const Dummy::Server::Command::Command& command
) {
    command.accept(*this);
}

std::unique_ptr<const Dummy::Server::Response::Response>
LoadingState::getResponse(Dummy::Protocol::IncomingPacket& packet)
{
    std::uint8_t response;
    packet >> response;
    switch(response) {
    case Dummy::Protocol::Bridge::TELEPORT_MAP:
        return _teleportMap(packet);
        break;
    default:
        break;
    }
    return nullptr;
}

void LoadingState::visitCommand(
    const Dummy::Server::Command::TeleportMap& teleportMap
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << Dummy::Protocol::Bridge::TELEPORT_MAP
        << teleportMap.mapName()
        << teleportMap.destination().first
        << teleportMap.destination().second
        << teleportMap.instance();
    m_networkConnector.sendPacket(pkt);
}

std::unique_ptr<const Dummy::Server::Response::TeleportMap>
LoadingState::_teleportMap(Dummy::Protocol::IncomingPacket& packet) {
    auto self(shared_from_this());
    std::unique_ptr<Dummy::Server::Response::TeleportMap> response =
        std::make_unique<Dummy::Server::Response::TeleportMap>();
    response->readFrom(packet);
    if (response->status() == 0) {
        m_networkConnector.changeState(
            std::make_shared<PlayingState>(m_networkConnector)
        );
    }
    return response;
}

} // namespace NetworkConnectorState
} // namespace Connector
