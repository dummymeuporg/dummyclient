#pragma once

#include <memory>

#include <dummy/server/command/command_visitor.hpp>

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

class Error : public std::exception {

};

class UnknownResponseError : public Error {
public:
    virtual const char* what() const noexcept override {
        return "the response code is incorrect";
    }
};

using CommandPtr = std::shared_ptr<const Dummy::Server::Command::Command>;

class State : public std::enable_shared_from_this<State>,
              public Dummy::Server::Command::CommandVisitor {
public:
    State(NetworkConnector&);

    virtual void sendCommand(CommandPtr) = 0;

    virtual
    std::shared_ptr<const Dummy::Server::Response::Response>
    getResponse(Dummy::Protocol::IncomingPacket&) = 0;

protected:
    NetworkConnector& m_networkConnector;
};

} // namespace NetworkConnectorState
} // namespace Connector
