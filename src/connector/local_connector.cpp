#include "server/game_session.hpp"
#include "server/response/response.hpp"
#include "connector/local_connector.hpp"

namespace Connector {

LocalConnector::LocalConnector(
    Dummy::Server::GameSession& gameSession
) : m_gameSession(gameSession) {}

void
LocalConnector::sendCommand(const Dummy::Server::Command::Command& command) {
    m_gameSession.handleCommand(command);
}

std::unique_ptr<const Dummy::Server::Response::Response>
LocalConnector::getResponse() {
    return m_gameSession.getResponse();
}

} // namespace Connector
