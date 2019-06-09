#include <iostream>
#include "protocol/bridge.hpp"
#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/command/command.hpp"
#include "server/command/connect_command.hpp"
#include "server/response/response.hpp"
#include "server/response/connect_response.hpp"
#include "connector/network_connector.hpp"
#include "connector/network_connector_state/initial_state.hpp"
#include "connector/network_connector_state/receive_primary_info_state.hpp"

namespace Connector {
namespace NetworkConnectorState {

InitialState::InitialState(NetworkConnector& networkConnector)
    : State(networkConnector)
{

}

void
InitialState::sendCommand(
    const Dummy::Server::Command::Command& command
) {
    command.accept(*this);
}


std::unique_ptr<const Dummy::Server::Response::Response>
InitialState::getResponse(Dummy::Protocol::IncomingPacket& packet)
{
    std::uint8_t response;
    packet >> response;
    switch(response) {
    case Dummy::Protocol::Bridge::CONNECT:
        return _getConnectResponse(packet);
        break;
    default:
        break;
    } 
    return nullptr;
}

void InitialState::visitCommand(
    const Dummy::Server::Command::ConnectCommand& connect
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << static_cast<std::uint16_t>(Dummy::Protocol::Bridge::CONNECT);
    pkt << connect.tagName() << connect.sessionID();
    m_networkConnector.sendPacket(pkt);
}

std::unique_ptr<const Dummy::Server::Response::ConnectResponse>
InitialState::_getConnectResponse(Dummy::Protocol::IncomingPacket& packet) {
    auto self(shared_from_this());
    std::unique_ptr<Dummy::Server::Response::ConnectResponse> response =
        std::make_unique<Dummy::Server::Response::ConnectResponse>();
    response->readFrom(packet);

    if (response->status() == 0) {
        m_networkConnector.changeState(
            std::make_shared<ReceivePrimaryInfoState>(m_networkConnector)
        );
    }
    return response;
}

} // namespace NetworkConnectorState
} // namespace Connector
