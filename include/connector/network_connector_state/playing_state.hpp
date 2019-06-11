#pragma once

#include "connector/network_connector_state/state.hpp"

namespace Dummy {
namespace Server {
namespace Command {
class Ping;
class SetPosition;
} // namespace Command

namespace Response {
class Ping;
class SetPosition;
} // namespace Response
} // namespace Server

namespace Protocol {
class IncomingPacket;
} // namespace Protocol
} // namespace Dummy

namespace Connector {
namespace NetworkConnectorState {

class PlayingState : public State {
public:
    PlayingState(NetworkConnector&);
    void sendCommand(const Dummy::Server::Command::Command&) override;

    std::unique_ptr<const Dummy::Server::Response::Response>
    getResponse(Dummy::Protocol::IncomingPacket&) override;

    void visitCommand(const Dummy::Server::Command::Ping&) override;
    void visitCommand(const Dummy::Server::Command::SetPosition&) override;
private:
    std::unique_ptr<const Dummy::Server::Response::Ping>
    _ping(Dummy::Protocol::IncomingPacket&);

    std::unique_ptr<const Dummy::Server::Response::SetPosition>
    _setPosition(Dummy::Protocol::IncomingPacket&);
};

} // namespace NetworkConnectorState
} // namespace Connector
