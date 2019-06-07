#include <iostream>
#include "protocol/bridge.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/command/command.hpp"
#include "server/command/connect_command.hpp"
#include "server/response/response.hpp"
#include "connector/network_connector.hpp"
#include "connector/network_connector_state/initial_state.hpp"

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
    std::cerr << "GOT PACKET!" << std::endl;
    return nullptr;
}

std::unique_ptr<const Dummy::Server::Response::Response>
InitialState::visitCommand(
    const Dummy::Server::Command::ConnectCommand& connect
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << static_cast<std::uint16_t>(Dummy::Protocol::Bridge::CONNECT);
    pkt << connect.tagName() << connect.sessionID();
    m_networkConnector.sendPacket(pkt);
    return nullptr; // no response to return
}



} // namespace NetworkConnectorState
} // namespace Connector
