#include <iostream>
#include <dummy/protocol/bridge.hpp>
#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/server/command/command.hpp>
#include <dummy/server/command/connect_command.hpp>
#include <dummy/server/response/response.hpp>
#include <dummy/server/response/connect_response.hpp>
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
InitialState::sendCommand(CommandPtr command) {
    command->accept(*this);
}


std::shared_ptr<const Dummy::Server::Response::Response>
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

std::shared_ptr<const Dummy::Server::Response::ConnectResponse>
InitialState::_getConnectResponse(Dummy::Protocol::IncomingPacket& packet) {
    auto self(shared_from_this());
    auto response =
        std::make_shared<Dummy::Server::Response::ConnectResponse>();
    response->readFrom(packet);

    if (response->status() == 0) {
        m_networkConnector.changeState(
            std::make_shared<ReceivePrimaryInfoState>(m_networkConnector)
        );
    } else {
        // Invalid status. Close the connection.
        m_networkConnector.close();
    }
    return std::move(response);
}

} // namespace NetworkConnectorState
} // namespace Connector
