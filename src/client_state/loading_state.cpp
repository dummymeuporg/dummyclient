#include <iostream>

#include "client.hpp"
#include "game.hpp"

#include "client_state/loading_state.hpp"

namespace ClientState {

LoadingState::LoadingState(::Client& client)
    : State(client), m_model(nullptr)
{

}

void LoadingState::resume() {
    std::cerr << "[LoadingState]" << std::endl;
    // What do we do?
    //
    // XXX: this sucks so much. I really need to figure it out.
    m_model = std::dynamic_pointer_cast<Model::LoadingModel>(
        m_client.game().screen()->model()
    );
}

void LoadingState::onRead(Dummy::Protocol::IncomingPacket& pkt) {
    std::cerr << "[LoadingState]" << std::endl;
    std::uint8_t answer;
    pkt >> answer;
    switch(answer) {
    case 1:
        std::cerr << "Good for teleporting" << std::endl;
        m_model->setStatus(1);
        m_model->update();
        break;
    default:
        break;
    }
}

} // namespace ClienState
