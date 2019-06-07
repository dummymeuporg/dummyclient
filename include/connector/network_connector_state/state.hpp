#pragma once

#include <memory>


namespace Dummy {
namespace Protocol {
class IncomingPacket;
} // namespace Protocol

namespace Server {
namespace Command {
class Command;
} // namespace Command

namespace Response {
class Response;
} // namespace Response

} // namespace Server
} // namespace Dummy

namespace Connector {
class NetworkConnector;
namespace NetworkConnectorState {

class State : public std::enable_shared_from_this<State> {
public:
    State(NetworkConnector&);

    virtual void
    sendCommand(const Dummy::Server::Command::Command&) = 0;

    virtual
    std::unique_ptr<const Dummy::Server::Response::Response>
    getResponse(Dummy::Protocol::IncomingPacket&) = 0;
private:
    NetworkConnector& m_networkConnector;
};

} // namespace NetworkConnectorState
} // namespace Connector
