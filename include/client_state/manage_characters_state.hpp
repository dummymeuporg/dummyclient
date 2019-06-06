#pragma once

#include "client_state/state.hpp"

namespace Model {
    class CharactersListModel;
}

namespace ClientState {

class ManageCharactersState : public State {
public:
    ManageCharactersState(::Client&,
                          std::shared_ptr<Model::CharactersListModel>);
    virtual void resume() override;
    virtual void onRead(Dummy::Protocol::IncomingPacket&) override;
    virtual void onResponse(const Dummy::Server::Response::Response&) override;
private:
    std::shared_ptr<Model::CharactersListModel> m_model;
};

} // namespace ClientState
