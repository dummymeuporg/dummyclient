#include <dummy/server/game_session_communicator.hpp>
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

void
LocalConnector::sendCommand(const Dummy::Server::Command::Command& command) {
    m_gameSessionCommunicator->forwardCommand(command);
}

} // namespace Connector
