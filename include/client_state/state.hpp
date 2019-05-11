#pragma once

#include <cstdint>
#include <memory>
#include <vector>

class Client;

namespace ClientState {

class State : public std::enable_shared_from_this<State> {
public:
    State(::Client&);
    virtual void resume() = 0;
    virtual void onRead(const std::vector<std::uint8_t>& buffer) = 0;
protected:
    ::Client& m_client;
};


} // namespace ClientState
