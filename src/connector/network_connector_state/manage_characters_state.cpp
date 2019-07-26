#include <iostream>

#include <dummy/protocol/bridge.hpp>
#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/server/command/command.hpp>
#include <dummy/server/command/create_character.hpp>
#include <dummy/server/command/select_character.hpp>
#include <dummy/server/response/response.hpp>
#include <dummy/server/response/create_character.hpp>
#include <dummy/server/response/select_character.hpp>

#include "connector/network_connector.hpp"
#include "connector/network_connector_state/loading_state.hpp"
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
    std::uint16_t response;
    packet >> response;
    switch(response) {
    case Dummy::Protocol::Bridge::CREATE_CHARACTER:
        return _createCharacter(packet);
        break;
    case Dummy::Protocol::Bridge::SELECT_CHARACTER:
        return _selectCharacter(packet);
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
    pkt << Dummy::Protocol::Bridge::CREATE_CHARACTER;
    pkt << create.name() << create.skin();
    // XXX: put character name and skin name
    m_networkConnector.sendPacket(pkt);
}

void ManageCharactersState::visitCommand(
    const Dummy::Server::Command::SelectCharacter& select
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << Dummy::Protocol::Bridge::SELECT_CHARACTER;
    pkt << select.name();
    // XXX: put character name
    m_networkConnector.sendPacket(pkt);

}

std::unique_ptr<const Dummy::Server::Response::CreateCharacter>
ManageCharactersState::_createCharacter(
    Dummy::Protocol::IncomingPacket& packet
) {
    std::unique_ptr<Dummy::Server::Response::CreateCharacter> response =
        std::make_unique<Dummy::Server::Response::CreateCharacter>();
    response->readFrom(packet);
    return response;
}

std::unique_ptr<const Dummy::Server::Response::SelectCharacter>
ManageCharactersState::_selectCharacter(
    Dummy::Protocol::IncomingPacket& packet
) {
    std::unique_ptr<Dummy::Server::Response::SelectCharacter> response =
        std::make_unique<Dummy::Server::Response::SelectCharacter>();
    response->readFrom(packet);
    if (response->status() == 0) {
        m_networkConnector.changeState(
            std::make_shared<LoadingState>(m_networkConnector)
        );
    }
    return response;
}

} // namespace NetworkConnectorState
} // namespace Connector
