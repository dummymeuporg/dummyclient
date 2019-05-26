#pragma once

#include "client_state/state.hpp"

namespace ClientState {

class LoadingState : public State {
public:
    LoadingState(::Client&);
    virtual void resume() override;
    virtual void onRead(Dummy::Protocol::IncomingPacket&) override;
};

} // namespace LoadingState
