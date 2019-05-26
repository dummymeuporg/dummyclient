#pragma once

#include "client_state/state.hpp"
#include "model/loading_model.hpp"

namespace ClientState {

class LoadingState : public State {
public:
    LoadingState(::Client&);
    virtual void resume() override;
    virtual void onRead(Dummy::Protocol::IncomingPacket&) override;
private:
    std::shared_ptr<Model::LoadingModel> m_model;
    
};

} // namespace LoadingState
