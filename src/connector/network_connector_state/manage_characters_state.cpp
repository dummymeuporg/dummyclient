#include <iostream>

#include "protocol/bridge.hpp"
#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/command/command.hpp"
#include "server/command/create_character.hpp"
#include "server/command/select_character.hpp"
#include "server/response/response.hpp"
#include "server/response/create_character.hpp"
#include "server/response/select_character.hpp"
#include "connector/network_connector.hpp"
#include "connector/network_connector_state/manage_characters_state.hpp"

namespace Connector {
namespace NetworkConnectorState {

ManageCharactersState::ManageCharactersState(
    NetworkConnector& networkConnector
) : State(networkConnector) {

}

void
ManageCharactersState::sendCommand(
    const Dummy::Server::Command::Command& command
) {
    command.accept(*this);
}


std::unique_ptr<const Dummy::Server::Response::Response>
ManageCharactersState::getResponse(Dummy::Protocol::IncomingPacket& packet)
{
    std::uint8_t response;
    packet >> response;
    switch(response) {
    case Dummy::Protocol::Bridge::CREATE_CHARACTER:
        //return _getCharactersListResponse(packet);
        break;
    case Dummy::Protocol::Bridge::SELECT_CHARACTER:
        // return
        break;
    default:
        throw UnknownResponseError();
        break;
    } 
    return nullptr;
}

void ManageCharactersState::visitCommand(
    const Dummy::Server::Command::CreateCharacter& create
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << static_cast<std::uint16_t>(
        Dummy::Protocol::Bridge::CREATE_CHARACTER
    );
    // XXX: put character name and skin name
    m_networkConnector.sendPacket(pkt);
}

void ManageCharactersState::visitCommand(
    const Dummy::Server::Command::SelectCharacter& select
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << static_cast<std::uint16_t>(
        Dummy::Protocol::Bridge::SELECT_CHARACTER
    );
    // XXX: put character name
    m_networkConnector.sendPacket(pkt);

}

std::unique_ptr<const Dummy::Server::Response::CreateCharacter>
ManageCharactersState::_createCharacter(
    Dummy::Protocol::IncomingPacket& packet
) {
    std::uint8_t status;
    packet >> status;
    std::unique_ptr<Dummy::Server::Response::CreateCharacter> response =
        std::make_unique<Dummy::Server::Response::CreateCharacter>();
    response->setStatus(status);
    return response;
}

std::unique_ptr<const Dummy::Server::Response::SelectCharacter>
ManageCharactersState::_selectCharacter(
    Dummy::Protocol::IncomingPacket& packet
) {
    std::uint8_t status;
    packet >> status;
    std::unique_ptr<Dummy::Server::Response::SelectCharacter> response =
        std::make_unique<Dummy::Server::Response::SelectCharacter>();
    response->setStatus(status);
    return response;
}

} // namespace NetworkConnectorState
} // namespace Connector
