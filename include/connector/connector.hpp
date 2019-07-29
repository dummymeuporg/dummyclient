#pragma once

#include <memory>
#include <queue>

#include <dummy/server/response/handler.hpp>

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

using ResponsePtr = std::unique_ptr<const Dummy::Server::Response::Response>;

class Connector : public Dummy::Server::Response::Handler {
public:
    Connector() {}

    void start();
    
    virtual void sendCommand(const Dummy::Server::Command::Command&) = 0;
    ResponsePtr getResponse();

    void handleResponse(ResponsePtr) override;
protected:
    std::queue<ResponsePtr> m_responses;
};


} // namespace Connector
