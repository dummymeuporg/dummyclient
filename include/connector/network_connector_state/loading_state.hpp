#pragma once

#include <memory>

#include "connector/network_connector_state/state.hpp"

namespace Dummy {
namespace Server {
namespace Command {
class TeleportMap;
} // namespace TeleportMap

namespace Response {
class TeleportMap;
} // namespace TeleportMap
} // namespace Server

namespace Protocol {
class IncomingPacket;
} // namespace Protocol
} // namespace Dummy

namespace Connector {
namespace NetworkConnectorState {

class LoadingState : public State {
public:
    LoadingState(NetworkConnector&);
    virtual void
    sendCommand(const Dummy::Server::Command::Command&) override;

    virtual std::unique_ptr<const Dummy::Server::Response::Response>
    getResponse(Dummy::Protocol::IncomingPacket&) override;

    virtual void
    visitCommand(const Dummy::Server::Command::TeleportMap&) override;
private:
    std::unique_ptr<const Dummy::Server::Response::TeleportMap>
    _teleportMap(Dummy::Protocol::IncomingPacket&);
};

} // namespace NetworkConnectorState
} // namespace Connector
