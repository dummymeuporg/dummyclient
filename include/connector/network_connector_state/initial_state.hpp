#pragma once

#include <memory>

#include "connector/network_connector_state/state.hpp"

namespace Dummy {
namespace Protocol {
class IncomingPacket;
} // namespace Protocol
} // namespace Dummy

namespace Connector {
namespace NetworkConnectorState {

class InitialState : public State {
public:
    InitialState(NetworkConnector&);
    virtual void
    sendCommand(const Dummy::Server::Command::Command&) override;

    virtual
    std::unique_ptr<const Dummy::Server::Response::Response>
    getResponse(Dummy::Protocol::IncomingPacket&) override;

    virtual
    std::unique_ptr<const Dummy::Server::Response::Response>
    visitCommand(const Dummy::Server::Command::ConnectCommand&) override;

};

} // namespace NetworkConnectorState
} // namespace Connector
