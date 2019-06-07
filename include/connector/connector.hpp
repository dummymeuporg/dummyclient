#pragma once

#include <memory>
#include <queue>

namespace Dummy {
namespace Server {
namespace Response {
class Response;
} // namespace Response
namespace Command {
class Command;
} // namespace Command
} // namespace Server
} // namespace Dummy

namespace Connector {

class Error : public std::exception {

};

class ConnectionError : public Error {
public:
    virtual const char* what() const noexcept override {
        return "error while connecting to the server";
    }
};

class Connector {
public:
    Connector() {}

    void start();
    
    virtual void
    sendCommand(const Dummy::Server::Command::Command&) = 0;

    virtual std::unique_ptr<const Dummy::Server::Response::Response>
    getResponse() = 0;
};


} // namespace Connector
