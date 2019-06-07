#pragma once

#include <memory>

#include "connector/network_connector_state/state.hpp"

namespace Dummy {
namespace Server {
namespace Command {
class GetPrimaryInfoCommand;
} // namespace Command

namespace Response {
class CharactersListResponse;
} // namespace Response
} // namespace Server

namespace Protocol {
class IncomingPacket;
} // namespace Protocol
} // namespace Dummy

namespace Connector {
namespace NetworkConnectorState {

class ReceivePrimaryInfoState : public State {
public:
    ReceivePrimaryInfoState(NetworkConnector&);
    virtual void
    sendCommand(const Dummy::Server::Command::Command&) override;

    virtual
    std::unique_ptr<const Dummy::Server::Response::Response>
    getResponse(Dummy::Protocol::IncomingPacket&) override;

    virtual
    std::unique_ptr<const Dummy::Server::Response::Response>
    visitCommand(const Dummy::Server::Command::GetPrimaryInfoCommand&)
    override;
private:
    std::unique_ptr<const Dummy::Server::Response::CharactersListResponse>
    _getCharactersListResponse(Dummy::Protocol::IncomingPacket&);

};

} // namespace NetworkConnectorState
} // namespace Connector
