#include <iostream>

#include <dummy/protocol/bridge.hpp>
#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/protocol/map_update/update.hpp>

#include <dummy/server/command/message.hpp>
#include <dummy/server/command/ping.hpp>
#include <dummy/server/command/set_position.hpp>

#include <dummy/server/response/message.hpp>
#include <dummy/server/response/ping.hpp>
#include <dummy/server/response/set_position.hpp>

#include "connector/network_connector.hpp"
#include "connector/network_connector_state/loading_state.hpp"
#include "connector/network_connector_state/playing_state.hpp"

namespace Connector {
namespace NetworkConnectorState {

PlayingState::PlayingState(NetworkConnector& networkConnector)
    : State(networkConnector)
{

}

void PlayingState::sendCommand(CommandPtr command) {
    command->accept(*this);
}

std::shared_ptr<const Dummy::Server::Response::Response>
PlayingState::getResponse(Dummy::Protocol::IncomingPacket& packet)
{
    std::uint16_t response;
    packet >> response;
    switch(response) {
    case Dummy::Protocol::Bridge::PING:
        return ping(packet);
        break;
    case Dummy::Protocol::Bridge::SET_POSITION:
        return setPosition(packet);
        break;
    case Dummy::Protocol::Bridge::MESSAGE:
        return message(packet);
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

void PlayingState::visitCommand(
    const Dummy::Server::Command::Message& message
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << Dummy::Protocol::Bridge::MESSAGE << message.content();
    m_networkConnector.sendPacket(pkt);
}

void PlayingState::visitCommand(
    const Dummy::Server::Command::ChangeCharacter&
) {
    Dummy::Protocol::OutgoingPacket pkt;
    pkt << Dummy::Protocol::Bridge::CHANGE_CHARACTER;
    m_networkConnector.sendPacket(pkt);
}

std::shared_ptr<const Dummy::Server::Response::Ping>
PlayingState::ping(Dummy::Protocol::IncomingPacket& packet) {
    std::shared_ptr<Dummy::Server::Response::Ping> response =
        std::make_shared<Dummy::Server::Response::Ping>();
    //response->readFrom(packet);
    // XXX: the response contains map updates. parse them manually hiere.
    response->readFrom(packet);
    return std::move(response);
}

std::shared_ptr<const Dummy::Server::Response::SetPosition>
PlayingState::setPosition(Dummy::Protocol::IncomingPacket& packet) {
    std::shared_ptr<Dummy::Server::Response::SetPosition> response =
    std::make_shared<Dummy::Server::Response::SetPosition>();
    response->readFrom(packet);
    return std::move(response);
}

std::shared_ptr<const Dummy::Server::Response::Message>
PlayingState::message(Dummy::Protocol::IncomingPacket& packet) {
    std::shared_ptr<Dummy::Server::Response::Message> response =
    std::make_shared<Dummy::Server::Response::Message>();
    response->readFrom(packet);
    return std::move(response);
}


} // namespace NetworkConnectorState
} // namespace Connector
