#include <iostream>

#include "protocol/bridge.hpp"
#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "protocol/map_update/update.hpp"
#include "server/command/ping.hpp"
#include "server/command/set_position.hpp"
#include "server/response/ping.hpp"
#include "server/response/set_position.hpp"
#include "connector/network_connector.hpp"
#include "connector/network_connector_state/loading_state.hpp"
#include "connector/network_connector_state/playing_state.hpp"

namespace Connector {
namespace NetworkConnectorState {

PlayingState::PlayingState(NetworkConnector& networkConnector)
    : State(networkConnector)
{

}

void PlayingState::sendCommand(
    const Dummy::Server::Command::Command& command
) {
    command.accept(*this);
}

std::unique_ptr<const Dummy::Server::Response::Response>
PlayingState::getResponse(Dummy::Protocol::IncomingPacket& packet)
{
    std::uint16_t response;
    packet >> response;
    switch(response) {
    case Dummy::Protocol::Bridge::PING:
        return _ping(packet);
        break;
    case Dummy::Protocol::Bridge::SET_POSITION:
        return _setPosition(packet);
        break;
    default:
        UnknownResponseError();
        break;
    }
    return nullptr;
}

void PlayingState::visitCommand(
    const Dummy::Server::Command::Ping& ping
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << Dummy::Protocol::Bridge::PING;
    m_networkConnector.sendPacket(pkt);
}

void PlayingState::visitCommand(
    const Dummy::Server::Command::SetPosition& setPosition
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << Dummy::Protocol::Bridge::SET_POSITION
        << setPosition.x() << setPosition.y();
    m_networkConnector.sendPacket(pkt);
}

std::unique_ptr<const Dummy::Server::Response::Ping>
PlayingState::_ping(Dummy::Protocol::IncomingPacket& packet) {
    std::unique_ptr<Dummy::Server::Response::Ping> response =
        std::make_unique<Dummy::Server::Response::Ping>();
    //response->readFrom(packet);
    // XXX: the response contains map updates. parse them manually hiere.
    response->readFrom(packet);
    return response;
}

std::unique_ptr<const Dummy::Server::Response::SetPosition>
PlayingState::_setPosition(Dummy::Protocol::IncomingPacket& packet) {
    std::unique_ptr<Dummy::Server::Response::SetPosition> response =
    std::make_unique<Dummy::Server::Response::SetPosition>();
    response->readFrom(packet);
    return response;
}

} // namespace NetworkConnectorState
} // namespace Connector
