#pragma once

#include "client_state/state.hpp"

namespace ClientState {

class InitialState : public State {
public:
    InitialState(::Client&);
    virtual void resume() override;
    virtual void onRead(const std::vector<std::uint8_t>& buffer) override;
};

} // namespace ClientState
