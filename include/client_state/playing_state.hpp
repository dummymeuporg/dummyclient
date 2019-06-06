#pragma once

#include "client_state/state.hpp"
#include "model/loading_model.hpp"

namespace Model {
    class PlayingModel;
}

namespace ClientState {

class PlayingState : public State {
public:
    PlayingState(::Client&, std::shared_ptr<Model::PlayingModel>);
    virtual void resume() override;
    virtual void onRead(Dummy::Protocol::IncomingPacket&) override;
    virtual void onResponse(const Dummy::Server::Response::Response&) override;
private:
    void _parseMapUpdates(Dummy::Protocol::IncomingPacket&);
    void _handleCharacterPosition(Dummy::Protocol::IncomingPacket&);
    void _handleCharacterOff(Dummy::Protocol::IncomingPacket&);

    std::shared_ptr<Model::PlayingModel> m_model;
};

}
