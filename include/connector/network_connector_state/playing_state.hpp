#pragma once

#include "connector/network_connector_state/state.hpp"

namespace Dummy {
namespace Server {
namespace Command {
class ChangeCharacter;
class Message;
class Ping;
class SetPosition;
} // namespace Command

namespace Response {
class ChangeCharacter;
class Message;
class Ping;
class SetPosition;
class TeleportMap;
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
    void sendCommand(CommandPtr) override;

    std::shared_ptr<const Dummy::Server::Response::Response>
    getResponse(Dummy::Protocol::IncomingPacket&) override;

    void visitCommand(const Dummy::Server::Command::Ping&) override;
    void visitCommand(const Dummy::Server::Command::SetPosition&) override;
    void visitCommand(const Dummy::Server::Command::Message&) override;
    void visitCommand(const Dummy::Server::Command::ChangeCharacter&) override;
    void visitCommand(const Dummy::Server::Command::TeleportMap&) override;
private:
    std::shared_ptr<const Dummy::Server::Response::Ping>
    ping(Dummy::Protocol::IncomingPacket&);

    std::shared_ptr<const Dummy::Server::Response::SetPosition>
    setPosition(Dummy::Protocol::IncomingPacket&);

    std::shared_ptr<const Dummy::Server::Response::Message>
    message(Dummy::Protocol::IncomingPacket&);

    std::shared_ptr<const Dummy::Server::Response::ChangeCharacter>
    changeCharacter(Dummy::Protocol::IncomingPacket&);

    std::shared_ptr<const::Dummy::Server::Response::TeleportMap>
    teleportMap(Dummy::Protocol::IncomingPacket&);
};

} // namespace NetworkConnectorState
} // namespace Connector
