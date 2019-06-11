#include <iostream>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/irange.hpp>

#include "protocol/bridge.hpp"
#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/command/command.hpp"
#include "server/command/connect_command.hpp"
#include "server/response/response.hpp"
#include "server/response/characters_list_response.hpp"
#include "connector/network_connector.hpp"
#include "connector/network_connector_state/receive_primary_info_state.hpp"
#include "connector/network_connector_state/manage_characters_state.hpp"

namespace Connector {
namespace NetworkConnectorState {

ReceivePrimaryInfoState::ReceivePrimaryInfoState(
    NetworkConnector& networkConnector
) : State(networkConnector) {

}

void
ReceivePrimaryInfoState::sendCommand(
    const Dummy::Server::Command::Command& command
) {
    command.accept(*this);
}


std::unique_ptr<const Dummy::Server::Response::Response>
ReceivePrimaryInfoState::getResponse(Dummy::Protocol::IncomingPacket& packet)
{
    std::uint8_t response;
    packet >> response;
    switch(response) {
    case Dummy::Protocol::Bridge::GET_PRIMARY_INFO:
        return _getCharactersListResponse(packet);
        break;
    default:
        break;
    } 
    return nullptr;
}

void ReceivePrimaryInfoState::visitCommand(
    const Dummy::Server::Command::GetPrimaryInfoCommand& info
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << Dummy::Protocol::Bridge::GET_PRIMARY_INFO;
    m_networkConnector.sendPacket(pkt);
}

std::unique_ptr<const Dummy::Server::Response::CharactersListResponse>
ReceivePrimaryInfoState::_getCharactersListResponse(
    Dummy::Protocol::IncomingPacket& packet
) {
    std::unique_ptr<Dummy::Server::Response::CharactersListResponse> response =
        std::make_unique<Dummy::Server::Response::CharactersListResponse>();
    response->readFrom(packet);

    m_networkConnector.changeState(
        std::make_shared<ManageCharactersState>(m_networkConnector)
    );
    
    return response;
}

} // namespace NetworkConnectorState
} // namespace Connector
