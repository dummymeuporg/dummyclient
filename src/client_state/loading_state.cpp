#include <iostream>

#include "client.hpp"
#include "game.hpp"

#include "client_state/loading_state.hpp"

namespace ClientState {

LoadingState::LoadingState(::Client& client)
    : State(client)
{

}

void LoadingState::resume() {
    std::cerr << "[LoadingState]" << std::endl;
    // What do we do?
    //
    // XXX: this sucks so much. I really need to figure it out.
    //m_model
}

void LoadingState::onRead(Dummy::Protocol::IncomingPacket& pkt) {
    std::cerr << "[LoadingState]" << std::endl;
    std::uint8_t answer;
    pkt >> answer;
    switch(answer) {
    case 1:
        std::cerr << "Good for teleporting" << std::endl;
        break;
    default:
        break;
    }
}

} // namespace ClienState
