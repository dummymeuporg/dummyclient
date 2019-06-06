#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "protocol/incoming_packet.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {
class Response;
} // namespace Response
} // namespace Server
} // namespace Dummy

class Client;

namespace ClientState {

class State : public std::enable_shared_from_this<State>,
              public Dummy::Server::Response::ResponseVisitor {
public:
    State(::Client&);
    virtual void resume() = 0;
    virtual void onRead(Dummy::Protocol::IncomingPacket&) = 0;
    virtual void onResponse(const Dummy::Server::Response::Response&) = 0;
protected:
    ::Client& m_client;
};


} // namespace ClientState
