#pragma once

#include <memory>

#include "connector/network_connector_state/state.hpp"

namespace Dummy {
namespace Server {
namespace Command {
class CreateCharacter;
class SelectCharacter;
} // namespace Command

namespace Response {
class CreateCharacter;
class SelectCharacter;
} // namespace Response
} // namespace Server

namespace Protocol {
class IncomingPacket;
} // namespace Protocol
} // namespace Dummy

namespace Connector {
namespace NetworkConnectorState {

class ManageCharactersState : public State {
public:
    ManageCharactersState(NetworkConnector&);
    virtual void sendCommand(CommandPtr) override;

    virtual
    std::shared_ptr<const Dummy::Server::Response::Response>
    getResponse(Dummy::Protocol::IncomingPacket&) override;

    virtual void
    visitCommand(const Dummy::Server::Command::CreateCharacter&)
    override;

    virtual void
    visitCommand(const Dummy::Server::Command::SelectCharacter&)
    override;

private:
    std::shared_ptr<const Dummy::Server::Response::CreateCharacter>
    _createCharacter(
        Dummy::Protocol::IncomingPacket& packet
    );

    std::shared_ptr<const Dummy::Server::Response::SelectCharacter>
    _selectCharacter(
        Dummy::Protocol::IncomingPacket& packet
    );
};

} // namespace NetworkConnectorState
} // namespace Connector
