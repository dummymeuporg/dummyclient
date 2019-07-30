#pragma once

#include <memory>

#include "connector/network_connector_state/state.hpp"

namespace Dummy {
namespace Server {
namespace Command {
class ConnectCommand;
} // namespace Command

namespace Response {
class ConnectResponse;
} // namespace Response
} // namespace Server

namespace Protocol {
class IncomingPacket;
} // namespace Protocol
} // namespace Dummy

namespace Connector {
namespace NetworkConnectorState {

class InitialState : public State {
public:
    InitialState(NetworkConnector&);
    virtual void sendCommand(CommandPtr) override;

    virtual
    std::shared_ptr<const Dummy::Server::Response::Response>
    getResponse(Dummy::Protocol::IncomingPacket&) override;

    virtual void
    visitCommand(const Dummy::Server::Command::ConnectCommand&) override;
private:
    std::shared_ptr<const Dummy::Server::Response::ConnectResponse>
    _getConnectResponse(Dummy::Protocol::IncomingPacket&);

};

} // namespace NetworkConnectorState
} // namespace Connector
