#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "protocol/incoming_packet.hpp"

class Client;

namespace ClientState {

class State : public std::enable_shared_from_this<State> {
public:
    State(::Client&);
    virtual void resume() = 0;
    virtual void onRead(Dummy::Protocol::IncomingPacket&) = 0;
protected:
    ::Client& m_client;
};


} // namespace ClientState
