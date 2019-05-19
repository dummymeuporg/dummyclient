#pragma once

#include "client_state/state.hpp"

namespace Model {
	class CharactersListModel;
}

namespace ClientState {

class ReceiveCharactersState : public State {
public:
    ReceiveCharactersState(::Client&);
    virtual void resume() override;
    virtual void onRead(Dummy::Protocol::IncomingPacket&) override;
private:
    std::shared_ptr<Model::CharactersListModel> m_model;
};

}  // namespace ClientState
