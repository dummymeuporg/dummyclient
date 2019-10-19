#include <iostream>

#include <dummy/server/game_session_communicator.hpp>
#include <dummy/server/command/command.hpp>
#include <dummy/server/response/response.hpp>
#include "connector/local_connector.hpp"

namespace Connector {

using GameSessionCommunicatorPtr =
    std::shared_ptr<Dummy::Server::GameSessionCommunicator>;

LocalConnector::LocalConnector(
    GameSessionCommunicatorPtr gameSessionCommunicator
) : m_gameSessionCommunicator(gameSessionCommunicator) {}

LocalConnector::~LocalConnector() {

    // XXX: inform the game session that we are done.
    // m_gameSession.close();
}

void LocalConnector::handleResponse(ResponsePtr response) {
    // Here, since the server and the client share the same memory space,
    // we need to disociate responses from both client pov and server pov.
    m_responses.emplace(response->clone());
}

void LocalConnector::start() {
    m_gameSessionCommunicator->setResponseHandler(shared_from_this());
}

void LocalConnector::sendCommand(CommandPtr command) {
    m_gameSessionCommunicator->forwardCommand(std::move(command));
}

} // namespace Connector
