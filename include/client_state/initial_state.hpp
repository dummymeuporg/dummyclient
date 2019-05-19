#pragma once

#include "client_state/state.hpp"

namespace ClientState {

class InitialState : public State {
public:
    InitialState(::Client&);
    virtual void resume() override;
    virtual void onRead(Dummy::Protocol::IncomingPacket&) override;
};

} // namespace ClientState
