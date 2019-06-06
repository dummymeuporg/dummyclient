#pragma once

#include "connector/connector.hpp"

namespace Dummy {
namespace Server {
class GameSession;

namespace Response {
class Response;
} // namespace Response
} // namespace Server
} // namespace Dummy

namespace Connector {

class LocalConnector : public Connector {
public:
    LocalConnector(Dummy::Server::GameSession&);
    virtual void
    sendCommand(const Dummy::Server::Command::Command&) override;

    virtual std::unique_ptr<const Dummy::Server::Response::Response>
    getResponse() override;
private:
    Dummy::Server::GameSession& m_gameSession;
    std::queue<std::unique_ptr<Dummy::Server::Response::Response>>
        m_responses;
};

}; // namespace Connector
