#include "server/game_session.hpp"
#include "server/response/response.hpp"
#include "connector/local_connector.hpp"

namespace Connector {

LocalConnector::LocalConnector(
    Dummy::Server::GameSession& gameSession
) : m_gameSession(gameSession) {}

void
LocalConnector::sendCommand(const Dummy::Server::Command::Command& command) {
    m_responses.emplace(std::move(m_gameSession.handleCommand(command)));
}

std::unique_ptr<const Dummy::Server::Response::Response>
LocalConnector::getResponse() {
    if (m_responses.size() > 0) {
        std::unique_ptr<Dummy::Server::Response::Response> r(
            std::move(m_responses.front())
        );
        m_responses.pop();
        return r;
    }
    return nullptr;
}

} // namespace Connector
