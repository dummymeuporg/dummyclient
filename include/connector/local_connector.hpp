#pragma once

#include "connector/connector.hpp"

namespace Dummy {
namespace Server {
class GameSessionCommunicator;

namespace Response {
class Response;
} // namespace Response
} // namespace Server
} // namespace Dummy

namespace Connector {

using CommandPtr = std::shared_ptr<const Dummy::Server::Command::Command>;

class LocalConnector : public Connector {
public:
    LocalConnector(std::shared_ptr<Dummy::Server::GameSessionCommunicator>);
    void start() override;
    virtual ~LocalConnector();
    void sendCommand(CommandPtr) override;
private:
    std::shared_ptr<Dummy::Server::GameSessionCommunicator>
        m_gameSessionCommunicator;

};

}; // namespace Connector
