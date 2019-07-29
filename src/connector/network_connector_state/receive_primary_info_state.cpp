#include <iostream>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/irange.hpp>

#include <dummy/protocol/bridge.hpp>
#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/server/command/command.hpp>
#include <dummy/server/command/connect_command.hpp>
#include <dummy/server/response/response.hpp>
#include <dummy/server/response/characters_list_response.hpp>

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
ReceivePrimaryInfoState::sendCommand(CommandPtr command) {
    command->accept(*this);
}


std::shared_ptr<const Dummy::Server::Response::Response>
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

std::shared_ptr<const Dummy::Server::Response::CharactersListResponse>
ReceivePrimaryInfoState::_getCharactersListResponse(
    Dummy::Protocol::IncomingPacket& packet
) {
    std::shared_ptr<Dummy::Server::Response::CharactersListResponse> response =
        std::make_shared<Dummy::Server::Response::CharactersListResponse>();
    response->readFrom(packet);

    m_networkConnector.changeState(
        std::make_shared<ManageCharactersState>(m_networkConnector)
    );
    
    return std::move(response);
}

} // namespace NetworkConnectorState
} // namespace Connector
